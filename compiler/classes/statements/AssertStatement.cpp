#include "AssertStatement.h"

AssertStatement::AssertStatement(Expression *expression)
    : expression_(expression) {}

void AssertStatement::Run() { assert(expression_->Count()); }

void AssertStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
