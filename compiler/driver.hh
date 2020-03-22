#pragma once

#include <map>
#include <string>
#include <fstream>
#include "scanner.h"
#include "parser.hh"

#include "classes/Program.h"
#include "visitors/SymbolTreeVisitor.h"
#include "symbol_table/ScopeLayer.h"
#include "visitors/Executor.h"

class Driver {
 public:
  Driver();
  int Parse(const std::string& file);
  std::string file_;
  bool trace_parsing_;

  void ScanBegin();
  void ScanEnd();

  void Exec();

  bool trace_scanning_;
  yy::location location_;

  friend class Scanner;
  Scanner scanner_;
  yy::parser parser_;
  Program* program_;

 private:
  std::ifstream stream_;
};
