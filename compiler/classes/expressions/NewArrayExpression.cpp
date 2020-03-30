#include "NewArrayExpression.h"

NewArrayExpression::NewArrayExpression(Type* type_name,
                                       Expression* length)
    : type_name_(type_name), length_(length) {}

void NewArrayExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
