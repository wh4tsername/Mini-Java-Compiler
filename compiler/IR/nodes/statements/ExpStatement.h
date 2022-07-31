#pragma once

#include "../expressions/Expression.h"
#include "Statement.h"

namespace IRT {
class ExpStatement : public Statement {
 public:
  explicit ExpStatement(Expression* expression);
  ~ExpStatement() override = default;

  bool IsExp() override;
  void Accept(Visitor* visitor) override;

  Expression* expression_;
};
}  // namespace IRT
