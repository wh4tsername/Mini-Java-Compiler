#include "NewArrayExpression.h"

NewArrayExpression::NewArrayExpression(Type* type_name,
                                       Expression* index_expression)
    : type_name_(type_name), index_expression_(index_expression) {}

int NewArrayExpression::Count() { return 0; }
