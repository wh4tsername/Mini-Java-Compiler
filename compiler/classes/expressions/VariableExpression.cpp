#include "VariableExpression.h"

VariableExpression::VariableExpression(std::string variable_name)
    : variable_name_(std::move(variable_name)) {}

void VariableExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
