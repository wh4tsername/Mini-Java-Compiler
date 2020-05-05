#pragma once

#include <string>

#include "Expression.h"
#include "VariableExpression.h"

class LengthExpression : public Expression {
 public:
  explicit LengthExpression(std::string variable_name);

  void Accept(Visitor* visitor) override;

  std::string variable_name_;
};
