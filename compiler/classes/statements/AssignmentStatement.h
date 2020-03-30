#pragma once

#include "../Lvalue.h"
#include "../expressions/Expression.h"
#include "Statement.h"

class AssignmentStatement : public Statement {
 public:
  explicit AssignmentStatement(Lvalue* lvalue, Expression* expression);

  void Accept(Visitor* visitor) override;

  Lvalue* lvalue_;
  Expression* expression_;
};
