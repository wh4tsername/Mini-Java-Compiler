#pragma once

#include "../../generators/Temporary.h"
#include "../expressions/Expression.h"

namespace IRT {
class TempExpression : public Expression {
 public:
  explicit TempExpression(IRT::Temporary temporary);
  void Accept(IRT::Visitor* visitor) override;

  bool IsTEMP() override;

  Temporary temporary_;
};
}  // namespace IRT
