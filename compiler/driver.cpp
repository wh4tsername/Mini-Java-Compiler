#include "driver.hh"
#include "parser.hh"

Driver::Driver() :
    trace_parsing_(false),
    trace_scanning_(false),
    scanner_(*this), parser_(scanner_, *this) {
}

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
  SymbolTreeVisitor visitor;
  visitor.Visit(program_);

  std::cout << "symbol_tree_built" << std::endl;

  Executor executor(visitor.GetRoot());
  executor.Exec();
}

void Driver::ScanEnd()
{
  stream_.close();
}
