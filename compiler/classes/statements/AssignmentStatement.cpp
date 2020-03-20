#include "AssignmentStatement.h"

AssignmentStatement::AssignmentStatement(Lvalue* lvalue, Expression* expression)
    : lvalue_(lvalue), expression_(expression) {}

void AssignmentStatement::Run() {}

void AssignmentStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
