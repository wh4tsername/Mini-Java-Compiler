#pragma once

#include "../Type.h"
#include "Expression.h"

class NewVariableExpression : public Expression {
 public:
  explicit NewVariableExpression(Type* variable_type);

  int Count() final;

 private:
  Type* variable_type_;
};
