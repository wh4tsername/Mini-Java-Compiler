#pragma once

#include <string>
#include <utility>

#include "Expression.h"

class LogicalExpression : Expression {
 public:
  LogicalExpression(std::string operation, Expression* lhs, Expression* rhs);

  int Count() final;

 private:
  std::string operation_;
  Expression* lhs_;
  Expression* rhs_;
};
