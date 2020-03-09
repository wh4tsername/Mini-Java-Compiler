#include "ArrayType.h"

ArrayType::ArrayType(Type* type) : Type(std::move(type->GetType())) {}
