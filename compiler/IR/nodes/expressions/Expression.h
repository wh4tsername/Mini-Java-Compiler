#pragma once

#include "../BaseElement.h"

namespace IRT {
class Expression : public BaseElement {
 public:
  virtual bool IsESEQ() {
    return false;
  }

  virtual bool IsCONST() {
    return false;
  }

  virtual bool IsNAME() {
    return false;
  }

  ~Expression() override = default;
};
}
