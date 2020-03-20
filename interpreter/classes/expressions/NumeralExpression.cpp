#include "NumeralExpression.h"

NumeralExpression::NumeralExpression(int value) : value_(value) {}

int NumeralExpression::Count() { return value_; }

void NumeralExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
