#include "ArrayValue.h"
#include "VariableValue.h"

void ArrayValue::SetValue(int value) {
  throw std::runtime_error("Can't set value to Array object");
}
int ArrayValue::GetValue() {
  throw std::runtime_error("Can't get 'int' value from Array object");
}
std::unordered_map<Symbol, Value*> ArrayValue::GetFields() {
  throw std::runtime_error("Can't get fields from Array Object");
}

void ArrayValue::SetValue(Value* value) {
  auto array = dynamic_cast<ArrayValue*>(value);
  this->Resize(array->GetSize());
  for (size_t i = 0; i < buffer_.size(); ++i) {
    buffer_[i]->SetValue(array->buffer_[i]);
  }
}

PrimitiveSimpleObject* ArrayValue::GetElementType() { return element_type_; }

Value* ArrayValue::AtIndex(size_t index) {
  if (index >= buffer_.size()) {
    throw std::runtime_error("Index out of bounds");
  } else {
    return buffer_[index];
  }
}
void ArrayValue::SetAtIndex(Value* value, size_t index) {
  if (value->GetType()->GetTypename() !=
      this->GetElementType()->GetTypename()) {
    throw std::runtime_error("Trying to set value of another type");
  } else if (index >= buffer_.size()) {
    throw std::runtime_error("Index out of bounds");
  } else {
    buffer_[index] = value;
  }
}
ArrayValue::ArrayValue(PrimitiveArrayObject* array_type)
    : type_(array_type), element_type_(array_type->simple_object_) {}
PrimitiveArrayObject* ArrayValue::GetType() { return type_; }
void ArrayValue::Resize(size_t size) {
  buffer_.clear();
  for (size_t i = 0; i < size; ++i) {
    buffer_.push_back(new VariableValue(element_type_));
  }
}
int ArrayValue::GetSize() { return buffer_.size(); }
