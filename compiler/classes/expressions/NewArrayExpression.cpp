#include "NewArrayExpression.h"

NewArrayExpression::NewArrayExpression(Type* type_name,
                                       Expression* length)
    : type_name_(new Type(type_name->type_name_ + "[]")), length_(length) {
  delete type_name;
}

void NewArrayExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
