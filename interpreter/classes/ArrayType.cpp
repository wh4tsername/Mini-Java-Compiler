#include "ArrayType.h"

ArrayType::ArrayType(Type* type) : Type(std::move(type->GetType())) {}

void ArrayType::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
