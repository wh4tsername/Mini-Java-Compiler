#pragma once

#include <fstream>
#include <map>
#include <string>
#include "parser.hh"
#include "scanner.h"

#include "IR/visitors/DoubleCallEliminateVisitor.h"
#include "IR/visitors/ESEQEliminator.h"
#include "IR/visitors/Linearizer.h"
#include "IR/visitors/PrintVisitor.h"
#include "classes/Program.h"
#include "function_processing/ClassStorage.h"
#include "objects/Method.h"
#include "symbol_table/NewScopeLayer.h"
#include "visitors/IRTreeBuildVisitor.h"
#include "visitors/NewFunctionProcessingVisitor.h"
#include "visitors/NewSymbolTreeVisitor.h"
#include "visitors/PrintTreeVisitor.h"
#include "visitors/TypeCheckingVisitor.h"

class Driver {
 public:
  Driver();
  int Parse(const std::string& file);
  std::string file_;
  bool trace_parsing_;

  void ScanBegin();
  void ScanEnd();

  void Exec() const;

  void SetLogsPath(std::string logs_path);
  void PrintTree(const std::string& filename) const;

  bool trace_scanning_;
  yy::location location_;

  friend class Scanner;
  Scanner scanner_;
  yy::parser parser_;
  Program* program_;

 private:
  std::ifstream stream_;
  std::string logs_path_;
};
