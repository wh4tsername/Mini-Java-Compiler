#pragma once

#include <string>

#include "Expression.h"

class VariableExpression : public Expression {
 public:
  explicit VariableExpression(std::string variable_name);

  void Accept(Visitor* visitor) override;

  std::string variable_name_;
};
