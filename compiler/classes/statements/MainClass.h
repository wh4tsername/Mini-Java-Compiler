#pragma once

#include "ListOfStatements.h"
#include "Statement.h"

#include <string>

class MainClass : public Statement {
 public:
  MainClass(std::string main_class_name, ListOfStatements* main_statements,
            ListOfStatements* declarations);

  void Accept(Visitor* visitor) override;

  std::string main_class_name_;
  ListOfStatements* main_statements_;
  ListOfStatements* declarations_;
};
