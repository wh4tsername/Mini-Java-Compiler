#include "FrameEmulator.h"

FrameEmulator::FrameEmulator(const std::shared_ptr<Method>& function) {
  num_parameters = function->GetParamsNumber();

  AllocScope();
}

void FrameEmulator::SetParameters(const std::vector<Value*>& values) {
  if (num_parameters != values.size()) {
    throw std::runtime_error("Parameters number mismatch");
  }

  for (auto&& value : values) {
    parameters_.emplace_back(value);
  }
}

void FrameEmulator::SetFields(const std::vector<Value*>& values) {
  num_fields = values.size();

  for (auto&& value : values) {
    parameters_.emplace_back(value);
  }
}

size_t FrameEmulator::AllocVariable(PrimitiveObject* primitive_object) {
  size_t index = variables_.size();
  if (primitive_object->IsArray()) {
    variables_.emplace_back(
        new ArrayValue(dynamic_cast<PrimitiveArrayObject*>(primitive_object)));
  } else {
    variables_.emplace_back(new VariableValue(
        dynamic_cast<PrimitiveSimpleObject*>(primitive_object)));
  }

  return index;
}

void FrameEmulator::AllocScope() { offsets_.push(variables_.size()); }

void FrameEmulator::DeallocScope() {
  size_t new_size = offsets_.top();
  offsets_.pop();

  // TODO(@wh4tsername) - Call destructors

  variables_.resize(new_size);
}

Value* FrameEmulator::Get(int index) {
  if (index >= 0) {
    return variables_.at(index);
  } else {
    return parameters_.at(-index - 1);
  }
}

void FrameEmulator::Set(int index, Value* value) {
  if (index >= 0) {
    variables_.at(index) = value;
  } else {
    parameters_.at(-index - 1) = value;
  }
}

void FrameEmulator::SetReturnValue(Value* value) { return_value_ = value; }

void FrameEmulator::SetParentFrame(FrameEmulator* frame) { parent_ = frame; }

void FrameEmulator::SetParentReturnValue(Value* value) {
  parent_->return_value_ = value;
}

bool FrameEmulator::HasParent() { return parent_ != nullptr; }

Value* FrameEmulator::GetReturnValue() const { return return_value_; }

int FrameEmulator::GetFieldSize() const { return num_fields; }
