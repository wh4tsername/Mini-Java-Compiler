#include "ReturnStatement.h"

ReturnStatement::ReturnStatement(Expression* expression)
    : expression_(expression) {}

void ReturnStatement::Run() {}

void ReturnStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
