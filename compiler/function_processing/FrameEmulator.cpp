#include "FrameEmulator.h"

FrameEmulator::FrameEmulator(const std::shared_ptr<Method>& function) {
  parameters_.resize(function->arguments_.size());
  num_parameters = function->arguments_.size();

  AllocScope();
}

void FrameEmulator::SetParameters(const std::vector<Object*>& values) {
  if (num_parameters != values.size()) {
    throw std::runtime_error("Parameters number mismatch");
  }

  for (auto&& value : values) {
    parameters_.emplace_back(value);
  }
}

void FrameEmulator::SetFields(const std::vector<Object*>& values) {
  num_fields = values.size();

  for (auto&& value : values) {
    parameters_.emplace_back(value);
  }
}

size_t FrameEmulator::AllocVariable() {
  // TODO(Arrays)
  size_t index = variables_.size();
  variables_.push_back(0);

  return index;
}

void FrameEmulator::AllocScope() {
  offsets_.push(variables_.size());
}

void FrameEmulator::DeallocScope() {
  size_t new_size = offsets_.top();
  offsets_.pop();

  // TODO(@wh4tsername) - Call destructors

  variables_.resize(new_size);
}

int FrameEmulator::Get(int index) {
  if (index >= 0) {
    return variables_.at(index);
  } else {
    return parameters_.at(-index - 1);
  }
}

void FrameEmulator::Set(int index, int value) {
  if (index >= 0) {
    variables_.at(index) = value;
  } else {
    parameters_.at(-index - 1) = value;
  }
}

void FrameEmulator::SetReturnValue(int value) {
  return_value_ = value;
}

void FrameEmulator::SetParentFrame(FrameEmulator *frame) {
  parent_ = frame;
}

void FrameEmulator::SetParentReturnValue(int value) {
  parent_->return_value_ = value;
}

bool FrameEmulator::HasParent() {
  return parent_ != nullptr;
}

int FrameEmulator::GetReturnValue() const {
  return return_value_;
}

int FrameEmulator::GetFieldSize() const {
  return num_fields;
}
