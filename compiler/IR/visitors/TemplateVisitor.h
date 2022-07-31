#pragma once

#include "../nodes/BaseElement.h"
#include "Visitor.h"

namespace IRT {
template <typename T>
class TemplateVisitor : public Visitor {
 public:
  T Accept(BaseElement* base_element);

 protected:
  T tos_value_;
};
}  // namespace IRT
