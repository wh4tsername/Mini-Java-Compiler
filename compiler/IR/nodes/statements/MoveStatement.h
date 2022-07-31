#pragma once

#include "../expressions/Expression.h"
#include "Statement.h"

namespace IRT {
class MoveStatement : public Statement {
 public:
  MoveStatement(Expression* source, Expression* target);

  void Accept(Visitor* visitor) override;

  Expression* source_;
  Expression* target_;
};
}  // namespace IRT
