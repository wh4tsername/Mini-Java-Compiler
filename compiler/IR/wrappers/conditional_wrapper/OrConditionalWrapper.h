#pragma once

#include "ConditionalWrapper.h"

namespace IRT {
class OrConditionalWrapper : public ConditionalWrapper {
 public:
  OrConditionalWrapper(SubtreeWrapper* first, SubtreeWrapper* second);
  Statement* ToConditional(Label true_label, Label false_label) override;

  SubtreeWrapper* first_;
  SubtreeWrapper* second_;
};
}  // namespace IRT
