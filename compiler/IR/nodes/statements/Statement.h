#pragma once

#include "../BaseElement.h"

namespace IRT {
class Statement : public BaseElement {
 public:
  virtual bool IsSeq() {
    return false;
  }

  virtual bool IsExp() {
    return false;
  }

  virtual ~Statement() = default;
};
}
