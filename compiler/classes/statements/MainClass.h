#pragma once

#include "ListOfStatements.h"
#include "Statement.h"

#include <string>

class MainClass : public Statement {
 public:
  MainClass(std::string main_class_name, MethodDeclaration* main,
            ListOfStatements* declarations);

  void Accept(Visitor* visitor) override;

  std::string main_class_name_;
  MethodDeclaration* main_;
  ListOfStatements* declarations_;
};
