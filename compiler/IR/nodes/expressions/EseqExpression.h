#pragma once

#include "../statements/Statement.h"
#include "Expression.h"

namespace IRT {
class EseqExpression : public Expression {
 public:
  bool IsESEQ() override;
  EseqExpression(Statement* statement, Expression* expression);

  void Accept(Visitor* visitor) override;

  Statement* statement_;
  Expression* expression_;
};
}  // namespace IRT
