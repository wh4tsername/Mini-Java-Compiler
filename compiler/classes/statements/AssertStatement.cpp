#include "AssertStatement.h"

AssertStatement::AssertStatement(Expression *expression)
    : expression_(expression) {}

void AssertStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
