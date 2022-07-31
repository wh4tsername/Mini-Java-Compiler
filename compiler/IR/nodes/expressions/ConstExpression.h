#pragma once

#include "Expression.h"

namespace IRT {
class ConstExpression : public Expression {
 public:
  explicit ConstExpression(int value);
  ~ConstExpression() override = default;

  bool IsCONST() override;
  int Value() const;

  void Accept(Visitor* visitor) override;

 private:
  int value_;
};
}
