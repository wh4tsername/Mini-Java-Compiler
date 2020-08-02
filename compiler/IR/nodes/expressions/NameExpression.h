#pragma once

#include "../../generators/Label.h"
#include "Expression.h"

namespace IRT {
class NameExpression : public Expression {
 public:
  NameExpression(Label label);
  bool IsNAME() override;

  void Accept(Visitor* visitor) override;

  Label label_;
};
}  // namespace IRT
