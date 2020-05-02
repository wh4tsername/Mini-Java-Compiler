#pragma once

#include <string>
#include "Expression.h"

class ArrayAccessExpression : public Expression {
 public:
  explicit ArrayAccessExpression(std::string array_indent,
                                 Expression* index_expression);

  void Accept(Visitor* visitor) override;

  std::string array_indent_;
  Expression* index_expression_;
};
