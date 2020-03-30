#pragma once

#include "../Formals.h"
#include "../Type.h"
#include "../expressions/Expression.h"
#include "ListOfStatements.h"
#include "Statement.h"

class MethodDeclaration : public Statement {
 public:
  explicit MethodDeclaration(std::string method_name, Type* type,
                             Formals* formals,
                             ListOfStatements* list_of_statements);

  void Accept(Visitor* visitor) override;

  Type* type_;
  Formals* formals_;
  ListOfStatements* list_of_statements_;
  std::string method_name_;
};
