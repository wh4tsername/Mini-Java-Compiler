#pragma once

#include "../visitors/Visitor.h"

namespace IRT {
class BaseElement {
 public:
  virtual ~BaseElement() = default;
  virtual void Accept(IRT::Visitor* visitor) = 0;
};
}
