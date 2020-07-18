#include "PrimitiveSimpleObject.h"
#include "../function_processing/ClassStorage.h"

PrimitiveSimpleObject::PrimitiveSimpleObject(Type* type) : type_(type) {
  is_class_ = !(type->type_name_ == "int" || type->type_name_ == "boolean");
}

bool PrimitiveSimpleObject::IsClass() { return is_class_; }

bool PrimitiveSimpleObject::IsArray() { return false; }

std::string PrimitiveSimpleObject::GetTypename() { return type_->type_name_; }

size_t PrimitiveSimpleObject::GetSize() {
  if (!is_class_) {
    return 4;
  } else {
    auto fields =
        ClassStorage::GetInstance().GetFields(Symbol(type_->type_name_));
    size_t size = 0;
    for (auto&& field : fields) {
      size += field.second->GetSize();
    }
    return size;
  }
}
