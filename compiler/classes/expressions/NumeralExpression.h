#pragma once

#include "Expression.h"

class NumeralExpression : public Expression {
 public:
  explicit NumeralExpression(int value);

  void Accept(Visitor* visitor) override;

 private:
  int value_;
};
