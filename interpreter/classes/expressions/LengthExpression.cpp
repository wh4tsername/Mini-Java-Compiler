#include "LengthExpression.h"

LengthExpression::LengthExpression(Expression* expression)
    : expression_(expression) {}

int LengthExpression::Count() {
  return 0;
}

void LengthExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
