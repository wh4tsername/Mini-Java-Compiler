#pragma once

#include <string>

#include "Expression.h"
#include "VariableExpression.h"

class LengthExpression : public Expression {
 public:
  explicit LengthExpression(Expression* expression);

  int Count() final;

  void Accept(Visitor* visitor) override;

 private:
  Expression* expression_;
};
