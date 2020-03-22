#include "Symbol.h"

Symbol::Symbol(std::string name) : name_(std::move(name)) {}

bool Symbol::operator==(const Symbol &other) const {
  return name_ == other.name_;
}

bool Symbol::operator!=(const Symbol &other) const {
  return name_ != other.name_;
}

std::string Symbol::GetName() const { return name_; }
