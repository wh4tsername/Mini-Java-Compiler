#pragma once

#include "../Lvalue.h"
#include "../expressions/Expression.h"
#include "Statement.h"

class AssignmentStatement : public Statement {
 public:
  explicit AssignmentStatement(Lvalue* lvalue, Expression* expression);

  void Run() final;

 private:
  Lvalue* lvalue_;
  Expression* expression_;
};