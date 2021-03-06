#pragma once

#include "../Type.h"
#include "Expression.h"

class NewVariableExpression : public Expression {
 public:
  explicit NewVariableExpression(Type* variable_type);

  void Accept(Visitor* visitor) override;

  Type* variable_type_;
};
