#pragma once

#include "Expression.h"

class NumeralExpression : public Expression {
 public:
  explicit NumeralExpression(int value);

  int Count() final;

 private:
  int value_;
};
