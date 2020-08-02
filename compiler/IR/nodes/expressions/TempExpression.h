#pragma once

#include "../expressions/Expression.h"
#include "../../generators/Temporary.h"

namespace IRT {
class TempExpression : public Expression {
 public:
  explicit TempExpression(IRT::Temporary  temporary);
  void Accept(IRT::Visitor* visitor) override;

  Temporary temporary_;
};
}
