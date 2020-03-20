#include "NewVariableExpression.h"

NewVariableExpression::NewVariableExpression(Type* variable_type)
    : variable_type_(variable_type) {}

int NewVariableExpression::Count() { return 0; }

void NewVariableExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
