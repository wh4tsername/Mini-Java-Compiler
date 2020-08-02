#include "TempExpression.h"

#include <utility>

void IRT::TempExpression::Accept(IRT::Visitor* visitor) {
  visitor->Visit(this);
}

IRT::TempExpression::TempExpression(IRT::Temporary  temporary)
    : temporary_(std::move(temporary)) {}
