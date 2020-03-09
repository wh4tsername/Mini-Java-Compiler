#pragma once

#include <vector>

#include "Expression.h"

class MethodExpression {
 public:
  explicit MethodExpression(Expression* init_expression);

  void AddExpression(Expression* expression);

 private:
  std::vector<Expression*> list_of_expressions_;
};
