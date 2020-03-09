#include "NewVariableExpression.h"

NewVariableExpression::NewVariableExpression(Type* variable_type)
    : variable_type_(variable_type) {}

int NewVariableExpression::Count() { return 0; }
