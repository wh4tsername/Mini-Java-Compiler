#include "driver.hh"
#include "../LogCleaner.h"
#include "parser.hh"

Driver::Driver()
    : program_(nullptr),
      trace_parsing_(false),
      trace_scanning_(false),
      scanner_(*this),
      parser_(scanner_, *this) {}

int Driver::Parse(const std::string& file) {
  file_ = file;
  location_.initialize(&file_);

  ScanBegin();

  parser_.set_debug_level(trace_parsing_);
  int return_code = parser_();
  std::cout << "parser " << return_code << std::endl;

  ScanEnd();

  return return_code;
}

void Driver::ScanBegin() {
  scanner_.set_debug(trace_scanning_);
  if (file_.empty() || file_ == "-") {
  } else {
    stream_.open(file_);
    std::cout << file_ << std::endl;
    scanner_.yyrestart(&stream_);
  }
}

void Driver::SetLogsPath(std::string logs_path) {
  logs_path_ = std::move(logs_path);
}

void Driver::Exec() const {
  std::string main_class_name = program_->main_class_->main_class_name_;

  NewSymbolTreeVisitor symbol_visitor;
  symbol_visitor.Visit(program_);

  std::cout << "symbol_tree_built" << std::endl;

  NewScopeLayerTree scope_tree = symbol_visitor.GetTree();

  TypeCheckingVisitor type_visitor(&scope_tree);
  type_visitor.Visit(program_);

  std::cout << "type_checking_done" << std::endl;

  ClassStorage& class_storage = ClassStorage::GetInstance();
  class_storage.Fill(scope_tree);

  auto main_method = scope_tree.methods_[Symbol(main_class_name + "$main")];

  std::shared_ptr<Method> main_object = std::get<1>(
      scope_tree.class_symbols_table_[Symbol(main_class_name)])[Symbol("main")];

  auto class_obj =
      new VariableValue(new PrimitiveSimpleObject(new Type(main_class_name)));
  NewFunctionProcessingVisitor func_visitor(
      &scope_tree, scope_tree.layer_mapping_[Symbol(main_class_name + "$main")],
      main_object, class_obj);

  func_visitor.SetParameters(std::vector<Value*>());
  func_visitor.Visit(main_method);

  std::cout << "func_calls_done" << std::endl;

  IRTreeBuildVisitor ir_tree_build_visitor(&scope_tree);
  ir_tree_build_visitor.Visit(program_);

  std::cout << "ir_tree_built" << std::endl;

  IrtMapping methods = ir_tree_build_visitor.GetTrees();

  LogCleaner& log_cleaner = LogCleaner::GetInstance();

  const size_t NUM_ITERATIONS = 15;
  for (const auto& func_view : methods) {
    IRT::PrintVisitor print_visitor_irt(logs_path_ + func_view.first +
                                        "_ir_tree.out");
    log_cleaner.AddLogFilePath(logs_path_ + func_view.first + "_ir_tree.out");

    methods[func_view.first]->Accept(&print_visitor_irt);

    // method bush printed

    IRT::DoubleCallEliminateVisitor call_eliminate_visitor;
    methods[func_view.first]->Accept(&call_eliminate_visitor);

    auto root_stmt = call_eliminate_visitor.GetTree();

    IRT::PrintVisitor print_visitor_double_call(logs_path_ + func_view.first +
                                                "_double_calls_eliminated.out");
    log_cleaner.AddLogFilePath(logs_path_ + func_view.first +
                               "_double_calls_eliminated.out");

    root_stmt->Accept(&print_visitor_double_call);

    // double calls eliminated

    IRT::ESEQEliminator eseq_eliminator;
    for (size_t i = 0; i < NUM_ITERATIONS; ++i) {
      root_stmt->Accept(&eseq_eliminator);
      root_stmt = eseq_eliminator.GetTree();
    }

    IRT::PrintVisitor print_visitor_eseq(logs_path_ + func_view.first +
                                         "_eseq_eliminated.out");
    log_cleaner.AddLogFilePath(logs_path_ + func_view.first +
                               "_eseq_eliminated.out");

    root_stmt->Accept(&print_visitor_eseq);

    // eseq eliminated

    IRT::Linearizer linearizer;
    for (size_t i = 0; i < NUM_ITERATIONS; ++i) {
      root_stmt->Accept(&linearizer);
      root_stmt = linearizer.GetTree();
    }

    IRT::PrintVisitor print_visitor_linearized(logs_path_ + func_view.first +
                                               "_linearized.out");
    log_cleaner.AddLogFilePath(logs_path_ + func_view.first +
                               "_linearized.out");

    root_stmt->Accept(&print_visitor_linearized);

    // linearized

    IRT::BlockFormerVisitor former(func_view.first);
    root_stmt->Accept(&former);
    root_stmt = former.GetTree();

    IRT::PrintVisitor print_visitor_blocks_formed(logs_path_ + func_view.first +
                                                  "_blocks_formed.out");
    log_cleaner.AddLogFilePath(logs_path_ + func_view.first +
                               "_blocks_formed.out");

    root_stmt->Accept(&print_visitor_blocks_formed);

    // blocks formed

    IRT::BlockBuilderVisitor block_builder;
    root_stmt->Accept(&block_builder);

    IRT::BlockGraph block_graph = block_builder.BuildGraph();
    block_graph.Print(logs_path_ + "block_graph_" + func_view.first + ".out");
    log_cleaner.AddLogFilePath(logs_path_ + "block_graph_" + func_view.first + ".out");

    // blocks built
  }

  std::cout << "blocks_built" << std::endl;

  // TODO delete root
}

void Driver::PrintTree(const std::string& filename) const {
  PrintTreeVisitor visitor(filename);
  visitor.Visit(program_);

  std::cout << "tree_printed" << std::endl;
}

void Driver::ScanEnd() { stream_.close(); }
