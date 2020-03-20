#pragma once

#include <string>
#include <utility>

#include "Expression.h"

class LogicalExpression : public Expression {
 public:
  LogicalExpression(std::string operation, Expression* lhs, Expression* rhs);

  int Count() final;

  void Accept(Visitor* visitor) override;

 private:
  std::string operation_;
  Expression* lhs_;
  Expression* rhs_;
};
