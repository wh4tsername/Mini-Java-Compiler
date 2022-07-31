#include "JumpConditionalStatement.h"

using namespace IRT;

JumpConditionalStatement::JumpConditionalStatement(LogicOperatorType type,
                                                   Expression *left,
                                                   Expression *right,
                                                   Label label_true,
                                                   Label label_false)
    : operator_type_(type),
      left_operand_(left),
      right_operand_(right),
      label_true_(label_true),
      label_false_(label_false) {}

void JumpConditionalStatement::Accept(Visitor *visitor) {
  visitor->Visit(this);
}
