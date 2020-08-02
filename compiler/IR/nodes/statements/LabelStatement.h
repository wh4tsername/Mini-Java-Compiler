#pragma once

#include "../../generators/Label.h"
#include "Statement.h"

namespace IRT {
class LabelStatement : public Statement {
 public:
  explicit LabelStatement(IRT::Label label);

  void Accept(Visitor* visitor) override;

  Label label_;
};
}  // namespace IRT
