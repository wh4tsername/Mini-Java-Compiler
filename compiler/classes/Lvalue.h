#pragma once

#include <string>
#include "../visitors/Node.h"
#include "expressions/Expression.h"

class Lvalue : public Node {
 public:
  explicit Lvalue(std::string variable_name,
                  ArrayAccessExpression* array_access_expression,
                  bool is_array);

  void Accept(Visitor* visitor) override;

  std::string variable_name_;
  ArrayAccessExpression* array_access_expression_;
  bool is_array_;
};
