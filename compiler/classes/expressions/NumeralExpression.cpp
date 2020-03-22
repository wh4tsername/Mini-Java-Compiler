#include "NumeralExpression.h"

NumeralExpression::NumeralExpression(int value) : value_(value) {}

void NumeralExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
