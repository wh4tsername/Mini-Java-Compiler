#pragma once

#include "ListOfStatements.h"
#include "Statement.h"

#include <string>

class MainClass : public Statement {
 public:
  MainClass(std::string main_class_name, ListOfStatements* list_of_statements);

  void Run() final;

 private:
  std::string main_class_name_;
  ListOfStatements* list_of_statements_;
};
