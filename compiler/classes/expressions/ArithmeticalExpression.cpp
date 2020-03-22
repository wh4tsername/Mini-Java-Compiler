#include "ArithmeticalExpression.h"

ArithmeticalExpression::ArithmeticalExpression(std::string operation,
                                               Expression* lhs, Expression* rhs)
    : operation_(std::move(operation)), lhs_(lhs), rhs_(rhs) {}

void ArithmeticalExpression::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
