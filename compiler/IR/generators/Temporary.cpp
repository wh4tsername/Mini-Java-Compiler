#include "Temporary.h"

IRT::Temporary::Temporary() : name_("%" + std::to_string(counter_++)) {}

IRT::Temporary::Temporary(std::string name) : name_(name) {}

std::string IRT::Temporary::ToString() const {
  return name_;
}

int IRT::Temporary::counter_ = 0;
