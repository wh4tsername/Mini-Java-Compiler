#include "LogicalExpression.h"

LogicalExpression::LogicalExpression(std::string operation, Expression* lhs,
                                     Expression* rhs)
    : operation_(std::move(operation)), lhs_(lhs), rhs_(rhs) {}

void LogicalExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
