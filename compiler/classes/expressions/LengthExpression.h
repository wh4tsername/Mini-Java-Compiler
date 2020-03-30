#pragma once

#include <string>

#include "Expression.h"
#include "VariableExpression.h"

class LengthExpression : public Expression {
 public:
  explicit LengthExpression(Expression* expression);

  void Accept(Visitor* visitor) override;

  Expression* expression_;
};
