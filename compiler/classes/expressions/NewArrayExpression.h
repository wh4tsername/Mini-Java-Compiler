#pragma once

#include "../Type.h"
#include "Expression.h"

class NewArrayExpression : public Expression {
 public:
  explicit NewArrayExpression(Type* type_name, Expression* index_expression);

  void Accept(Visitor* visitor) override;

 private:
  Type* type_name_;
  Expression* index_expression_;
};