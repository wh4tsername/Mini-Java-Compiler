#pragma once

#include "../SubtreeWrapper.h"

namespace IRT {
class ConditionalWrapper : public SubtreeWrapper {
 public:
  ~ConditionalWrapper() override = default;

  Expression* ToExpression() override;
  Statement* ToStatement() override;
};
}  // namespace IRT
