#include "LengthExpression.h"

LengthExpression::LengthExpression(Expression* expression)
    : expression_(expression) {}

void LengthExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
