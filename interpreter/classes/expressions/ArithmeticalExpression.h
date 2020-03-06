#pragma once

#include <iostream>
#include <string>
#include <utility>

#include "Expression.h"

class ArithmeticalExpression : public Expression {
 public:
  explicit ArithmeticalExpression(std::string operation, Expression* lhs,
                         Expression* rhs);

  int Count() final;

 private:
  std::string operation_;
  Expression* lhs_;
  Expression* rhs_;
};
