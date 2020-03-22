#pragma once

#include "Expression.h"

class ArrayAccessExpression : public Expression {
 public:
  explicit ArrayAccessExpression(Expression* main_expression,
                                 Expression* index_expression);

  void Accept(Visitor* visitor) override;

 private:
  Expression* main_expression_;
  Expression* index_expression_;
};
