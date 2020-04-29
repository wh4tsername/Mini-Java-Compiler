#include "Frame.h"

Frame::Frame(std::shared_ptr<Function> function) {
  parameters_.resize(function->arguments_.size());

  AllocScope();
}

void Frame::SetParameters(const std::vector<int> &values) {
  if (parameters_.size() != values.size()) {
    throw std::runtime_error("Parameters mismatch");
  }

  parameters_ = values;
}

void Frame::AllocScope() {
  offsets_.push(variables_.size());
}

void Frame::DeallocScope() {
  size_t new_size = offsets_.top();
  offsets_.pop();

  // TODO(@wh4tsername) - Call destructors

  variables_.resize(new_size);
}

size_t Frame::AllocVariable() {
  size_t index = variables_.size();
  variables_.push_back(0);

  return index;
}

int Frame::Get(int index) {
  if (index >= 0) {
    return variables_.at(index);
  } else {
    return parameters_.at(-index - 1);
  }
}

void Frame::Set(int index, int value) {
  if (index >= 0) {
    variables_.at(index) = value;
  } else {
    parameters_.at(-index - 1) = value;
  }
}

void Frame::SetReturnValue(int value) {
  return_value_ = value;
}

void Frame::SetParentFrame(Frame *frame) {
  parent_ = frame;
}

void Frame::SetParentReturnValue(int value) {
  parent_->return_value_ = value;
}

bool Frame::HasParent() {
  return parent_ != nullptr;
}

int Frame::GetReturnValue() const {
  return return_value_;
}
