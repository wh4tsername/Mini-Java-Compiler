#pragma once

#include "ListOfStatements.h"
#include "Statement.h"

#include <string>

class ClassDeclaration : public Statement {
 public:
  explicit ClassDeclaration(std::string class_name,
                            ListOfStatements* declarations);

  void Run() final;

  void Accept(Visitor* visitor) override;

 private:
  std::string class_name_;
  ListOfStatements* declarations_;
};
