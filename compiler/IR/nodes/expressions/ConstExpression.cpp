#include "ConstExpression.h"

void IRT::ConstExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}

IRT::ConstExpression::ConstExpression(int value) : value_(value) {}

int IRT::ConstExpression::Value() const {
  return value_;
}

bool IRT::ConstExpression::IsCONST() {
  return true;
}
