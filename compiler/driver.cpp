#include "driver.hh"
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

void Driver::Exec() {
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

  auto class_obj = new VariableValue(new PrimitiveSimpleObject(new Type(main_class_name)));
  NewFunctionProcessingVisitor func_visitor(
      &scope_tree, scope_tree.layer_mapping_[Symbol(main_class_name + "$main")],
      main_object, class_obj);

  func_visitor.Visit(main_method);

  std::cout << "func_calls_done" << std::endl;

  //  TODO(@wh4tsername) delete root
}

void Driver::PrintTree(const std::string& filename) {
  PrintTreeVisitor visitor(filename);
  visitor.Visit(program_);

  std::cout << "tree_printed" << std::endl;
}

void Driver::ScanEnd() { stream_.close(); }
