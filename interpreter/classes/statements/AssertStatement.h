#pragma once

#include "../expressions/Expression.h"
#include "Statement.h"

#include <cassert>

class AssertStatement : public Statement {
 public:
  explicit AssertStatement(Expression* expression);

  void Run() final;

  void Accept(Visitor* visitor) override;

 private:
  Expression* expression_;
};
