#include "NegativeConditionalWrapper.h"

using namespace IRT;

NegativeConditionalWrapper::NegativeConditionalWrapper(SubtreeWrapper* wrapper)
    : wrapper_(wrapper) {}

Statement* NegativeConditionalWrapper::ToConditional(Label true_label,
                                                     Label false_label) {
  return wrapper_->ToConditional(false_label, true_label);
}
