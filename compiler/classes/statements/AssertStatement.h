#pragma once

#include "../expressions/Expression.h"
#include "Statement.h"

#include <cassert>

class AssertStatement : public Statement {
 public:
  explicit AssertStatement(Expression* expression);

  void Accept(Visitor* visitor) override;

  Expression* expression_;
};
