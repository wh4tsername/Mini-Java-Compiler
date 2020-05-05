#include "ArrayType.h"

ArrayType::ArrayType(Type* type) : Type(std::move(type->type_name_ + "[]")) {}

void ArrayType::Accept(Visitor* visitor) { visitor->Visit(this); }
