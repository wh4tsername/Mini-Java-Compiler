#pragma once

#include <string>

#include "Expression.h"

class FieldAccess : public Expression {
 public:
  FieldAccess(std::string field_name);

  void Accept(Visitor* visitor);

  std::string field_name_;
};
