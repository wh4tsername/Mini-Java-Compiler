#include "VariableValue.h"

VariableValue::VariableValue(PrimitiveSimpleObject* type) : type_(type) {
  if (type_->IsClass()) {
    auto fields =
        ClassStorage::GetInstance().GetFields(Symbol(type_->type_->type_name_));
    for (const auto& field : fields) {
      if (field.second->IsArray()) {
        fields_[field.first] =
            new ArrayValue((PrimitiveArrayObject*)field.second.get());
      } else {
        fields_[field.first] =
            new VariableValue((PrimitiveSimpleObject*)field.second.get());
      }
    }
  } else {
    value_ = 0;
  }
}
VariableValue::VariableValue(PrimitiveSimpleObject* type, int value)
    : type_(type) {
  if (type_->IsClass()) {
    throw std::runtime_error("Trying to set 'int' value to Class object");
  } else {
    value_ = value;
  }
}
void VariableValue::SetValue(int value) {
  if (type_->IsClass()) {
    throw std::runtime_error("Trying to set 'int' value to Class object");
  } else {
    value_ = value;
  }
}
void VariableValue::SetValue(Value* object) {
  if (object->GetType()->GetTypename() == this->GetType()->GetTypename()) {
    type_ = (PrimitiveSimpleObject*)object->GetType();
  } else {
    throw std::runtime_error("Different types");
  }
  value_ = object->GetValue();
  fields_ = std::move(object->GetFields());
}
int VariableValue::GetValue() { return value_; }
std::unordered_map<Symbol, Value*> VariableValue::GetFields() {
  return fields_;
}

void VariableValue::SetField(const Symbol& field, Value* value) {
  if (fields_.find(field) == fields_.end()) {
    throw std::runtime_error("Trying to set value to undeclared field");
  }

  // TODO delete old Value*

  fields_[field] = value;
}

PrimitiveSimpleObject* VariableValue::GetType() { return type_; }
