#pragma once

#include "../Type.h"
#include "Expression.h"

class NewArrayExpression : public Expression {
 public:
  explicit NewArrayExpression(Type* type_name, Expression* length);

  void Accept(Visitor* visitor) override;

  Type* type_name_;
  Expression* length_;
};
