#pragma once

#include "Expression.h"

class This : public Expression {
 public:
  This() = default;

  int Count() final;
};