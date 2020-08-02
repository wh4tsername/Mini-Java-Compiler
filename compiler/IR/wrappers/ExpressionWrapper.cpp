#include "ExpressionWrapper.h"
#include "../nodes/expressions/ConstExpression.h"
#include "../nodes/statements/ExpStatement.h"
#include "../nodes/statements/JumpConditionalStatement.h"

using namespace IRT;

ExpressionWrapper::ExpressionWrapper(Expression* expression)
    : expression_(expression) {}

Expression* ExpressionWrapper::ToExpression() { return expression_; }

Statement* ExpressionWrapper::ToStatement() {
  return new ExpStatement(expression_);
}

Statement* ExpressionWrapper::ToConditional(Label true_label,
                                            Label false_label) {
  return new JumpConditionalStatement(LogicOperatorType::NE, expression_,
                                      new ConstExpression(0), true_label,
                                      false_label);
}
