#pragma once

#include <map>
#include <string>
#include <fstream>
#include "scanner.h"
#include "parser.hh"

#include "classes/Program.h"
#include "visitors/NewSymbolTreeVisitor.h"
#include "symbol_table/NewScopeLayer.h"
#include "visitors/TypeCheckingVisitor.h"
#include "visitors/PrintTreeVisitor.h"
#include "function_processing/ClassStorage.h"
#include "objects/Method.h"
#include "visitors/NewFunctionProcessingVisitor.h"
#include "visitors/IRTreeBuildVisitor.h"

class Driver {
 public:
  Driver();
  int Parse(const std::string& file);
  std::string file_;
  bool trace_parsing_;

  void ScanBegin();
  void ScanEnd();

  void Exec();

  void PrintTree(const std::string& filename);

  bool trace_scanning_;
  yy::location location_;

  friend class Scanner;
  Scanner scanner_;
  yy::parser parser_;
  Program* program_;

 private:
  std::ifstream stream_;
};
