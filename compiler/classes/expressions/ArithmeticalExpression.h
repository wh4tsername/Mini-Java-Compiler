#pragma once

#include <iostream>
#include <string>
#include <utility>

#include "Expression.h"

class ArithmeticalExpression : public Expression {
 public:
  explicit ArithmeticalExpression(std::string operation, Expression* lhs,
                         Expression* rhs);

  void Accept(Visitor* visitor) override;

  std::string operation_;
  Expression* lhs_;
  Expression* rhs_;
};
