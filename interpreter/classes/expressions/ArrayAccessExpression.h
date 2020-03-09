#pragma once

#include "Expression.h"

class ArrayAccessExpression : public Expression {
 public:
  explicit ArrayAccessExpression(Expression* main_expression,
                                 Expression* index_expression);

  int Count() final;

 private:
  Expression* main_expression_;
  Expression* index_expression_;
};
