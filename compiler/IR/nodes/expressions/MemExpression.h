#pragma once

#include "Expression.h"

namespace IRT {
class MemExpression : public Expression {
 public:
  explicit MemExpression(Expression* expression);

  void Accept(Visitor* visitor) override;

  Expression* expression_;
};
}
