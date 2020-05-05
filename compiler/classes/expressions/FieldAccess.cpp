#include "FieldAccess.h"

FieldAccess::FieldAccess(std::string field_name) : field_name_(std::move(field_name)) {}

void FieldAccess::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
