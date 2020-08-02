#pragma once

#include "SubtreeWrapper.h"

namespace IRT {
class StatementWrapper : public SubtreeWrapper {
 public:
  explicit StatementWrapper(Statement* statement);

  Expression* ToExpression() override;
  Statement* ToStatement() override;
  Statement* ToConditional(Label true_label, Label false_label) override;

  Statement* statement_;
};
}
