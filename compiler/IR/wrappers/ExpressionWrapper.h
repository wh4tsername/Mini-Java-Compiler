#pragma once

#include "../nodes/statements/Statement.h"
#include "SubtreeWrapper.h"

namespace IRT {
class ExpressionWrapper : public SubtreeWrapper {
 public:
  explicit ExpressionWrapper(Expression* expression);
  ~ExpressionWrapper() override = default;

  Expression* ToExpression() override;
  Statement* ToStatement() override;
  Statement* ToConditional(Label true_label, Label false_label) override;

 private:
  Expression* expression_;
};
}  // namespace IRT
