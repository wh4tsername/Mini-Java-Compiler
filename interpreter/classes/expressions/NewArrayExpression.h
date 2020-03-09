#pragma once

#include "../Type.h"
#include "Expression.h"

class NewArrayExpression : public Expression {
 public:
  explicit NewArrayExpression(Type* type_name, Expression* index_expression);

  int Count() final;

 private:
  Type* type_name_;
  Expression* index_expression_;
};
