#include "Formals.h"

void Formals::AddFormal(Type* type, const std::string& arg_name) {
  formals_.emplace_back(type, arg_name);
}

void Formals::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
