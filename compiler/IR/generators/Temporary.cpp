#include "Temporary.h"

#include <utility>

IRT::Temporary::Temporary() : name_("%" + std::to_string(counter_++)) {}

IRT::Temporary::Temporary(std::string name) : name_(std::move(name)) {}

std::string IRT::Temporary::ToString() const {
  return name_;
}

bool IRT::Temporary::operator==(const IRT::Temporary& other) const {
  return (name_ == other.name_);
}

bool IRT::Temporary::operator!=(const IRT::Temporary& other) const {
  return (name_ != other.name_);
}

int IRT::Temporary::counter_ = 0;
