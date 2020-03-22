#include "NewArrayExpression.h"

NewArrayExpression::NewArrayExpression(Type* type_name,
                                       Expression* index_expression)
    : type_name_(type_name), index_expression_(index_expression) {}

void NewArrayExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
