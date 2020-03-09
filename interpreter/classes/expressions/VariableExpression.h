#pragma once

#include <string>

#include "Expression.h"

class VariableExpression : public Expression {
 public:
  explicit VariableExpression(std::string variable_name);

  int Count() final;

 private:
  std::string variable_name_;
};
