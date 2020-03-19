#include "NumeralExpression.h"

NumeralExpression::NumeralExpression(int value) : value_(value) {}

int NumeralExpression::Count() { return value_; }
