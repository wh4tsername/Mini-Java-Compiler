#include "RelativeConditionalWrapper.h"
#include "../../nodes/statements/JumpConditionalStatement.h"

using namespace IRT;

RelativeConditionalWrapper::RelativeConditionalWrapper(LogicOperatorType type,
                                                       Expression* lhs,
                                                       Expression* rhs)
    : operator_type_(type), lhs_(lhs), rhs_(rhs) {}

Statement* RelativeConditionalWrapper::ToConditional(Label true_label,
                                                     Label false_label) {
  return new JumpConditionalStatement(operator_type_, lhs_, rhs_, true_label,
                                      false_label);
}
