#pragma once

#include "ConditionalWrapper.h"

namespace IRT {
class NegativeConditionalWrapper : public ConditionalWrapper {
 public:
  explicit NegativeConditionalWrapper(SubtreeWrapper* wrapper);
  Statement* ToConditional(Label true_label, Label false_label);

  SubtreeWrapper* wrapper_;
};
}
