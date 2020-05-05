#include "LengthExpression.h"

LengthExpression::LengthExpression(std::string variable_name)
    : variable_name_(std::move(variable_name)) {}

void LengthExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
