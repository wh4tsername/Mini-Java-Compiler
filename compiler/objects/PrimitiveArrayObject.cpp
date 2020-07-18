#include "PrimitiveArrayObject.h"

PrimitiveArrayObject::PrimitiveArrayObject(ArrayType* type)
    : simple_object_(new PrimitiveSimpleObject(new Type(std::string(
          type->type_name_.begin(), type->type_name_.end() - 2)))) {}

std::string PrimitiveArrayObject::GetTypename() {
  return simple_object_->GetTypename() + "[]";
}

bool PrimitiveArrayObject::IsArray() { return true; }

PrimitiveArrayObject::PrimitiveArrayObject(
    PrimitiveSimpleObject* primitive_simple_object)
    : simple_object_(primitive_simple_object) {}

std::size_t PrimitiveArrayObject::GetSize() {
  // TODO size of pointer

  return simple_object_->GetSize();
}
