#pragma once

#include "../../generators/Label.h"
#include "../../types/LogicOperatorType.h"
#include "../expressions//Expression.h"
#include "Statement.h"

namespace IRT {
class JumpConditionalStatement : public Statement {
 public:
  JumpConditionalStatement(LogicOperatorType type, Expression* left,
                           Expression* right, Label label_true,
                           Label label_false);

  void Accept(Visitor* visitor) override;

  LogicOperatorType operator_type_;
  Label label_true_;
  Label label_false_;
  Expression* left_operand_;
  Expression* right_operand_;
};
}  // namespace IRT
