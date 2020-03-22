#pragma once

#include "Expression.h"

class This : public Expression {
 public:
  This() = default;

  void Accept(Visitor* visitor) override;
};
