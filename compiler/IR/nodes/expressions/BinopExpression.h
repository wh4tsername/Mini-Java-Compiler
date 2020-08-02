#pragma once

#include "../../types/BinaryOperatorType.h"
#include "Expression.h"

namespace IRT {
class BinopExpression : public Expression {
 public:
  BinopExpression(BinaryOperatorType type, Expression* lhs, Expression* rhs);

  void Accept(IRT::Visitor* visitor) override;

  BinaryOperatorType type_;
  Expression* lhs_;
  Expression* rhs_;
};
}  // namespace IRT
