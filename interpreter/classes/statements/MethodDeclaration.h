#pragma once

#include "../Formals.h"
#include "../Type.h"
#include "../expressions/Expression.h"
#include "ListOfStatements.h"
#include "Statement.h"

class MethodDeclaration : public Statement {
 public:
  explicit MethodDeclaration(Type* type, Formals* formals,
                             ListOfStatements* list_of_statements);

  void Run() final;

 private:
  Type* type_;
  Formals* formals_;
  ListOfStatements* list_of_statements_;
};
