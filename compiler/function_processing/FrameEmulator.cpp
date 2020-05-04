#include "FrameEmulator.h"

FrameEmulator::FrameEmulator(std::shared_ptr<Method> function) {
  parameters_.resize(function->arguments_.size());

  AllocScope();
}

void FrameEmulator::SetParameters(const std::vector<int> &values) {
  if (parameters_.size() != values.size()) {
    throw std::runtime_error("Parameters mismatch");
  }

  parameters_ = values;
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

size_t FrameEmulator::AllocVariable() {
  size_t index = variables_.size();
  variables_.push_back(0);

  return index;
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
