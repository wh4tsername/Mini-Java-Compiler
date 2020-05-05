#pragma once

#include <string>

#include "../visitors/Node.h"
#include "expressions/Expression.h"

class Lvalue : public Node {
 public:
  enum CODE {
    VAR = 0,
    ARR,
    FIELD
  };

  explicit Lvalue(std::string variable_name,
                  ArrayAccessExpression* array_access_expression,
                  FieldAccess* field_access,
                  int code);

  void Accept(Visitor* visitor) override;

  std::string variable_name_;
  ArrayAccessExpression* array_access_expression_;
  FieldAccess* field_access_;
  int code_;
};
