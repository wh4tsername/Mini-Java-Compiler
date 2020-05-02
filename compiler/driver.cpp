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
  SymbolTreeVisitor symbol_visitor;
  symbol_visitor.Visit(program_);

  std::cout << "symbol_tree_built" << std::endl;

  auto root = symbol_visitor.GetRoot();

  auto functions = symbol_visitor.GetFunctions();

  FunctionStorage& storage = FunctionStorage::GetInstance();
  for (const auto& pair : functions) {
    storage.Set(pair.first, pair.second);
  }

  MethodDeclaration* main_function = storage.Get(Symbol("main"));

  std::shared_ptr<Function> function_type =
      std::dynamic_pointer_cast<Function>(root.Get(Symbol("main")));

  FunctionProcessingVisitor func_visitor(root.GetFunctionScope(Symbol("main")),
                                         function_type);
  func_visitor.SetTree(&root);
  func_visitor.Visit(main_function);
  // TODO(@wh4tsername) exec somehow
  // TODO(@wh4tsername) delete root
}

void Driver::PrintTree(const std::string& filename) {
  PrintTreeVisitor visitor(filename);
  visitor.Visit(program_);

  std::cout << "tree_printed" << std::endl;
}

void Driver::ScanEnd() { stream_.close(); }
