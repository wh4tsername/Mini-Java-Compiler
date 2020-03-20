#pragma once

#include "Expression.h"

class NumeralExpression : public Expression {
 public:
  explicit NumeralExpression(int value);

  int Count() final;

  void Accept(Visitor* visitor) override;

 private:
  int value_;
};
