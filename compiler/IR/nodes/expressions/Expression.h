#pragma once

#include "../BaseElement.h"

namespace IRT {
class Expression : public BaseElement {
 public:
  virtual bool IsESEQ() { return false; }

  virtual bool IsCONST() { return false; }

  virtual bool IsNAME() { return false; }

  virtual bool IsTEMP() { return false; }

  virtual bool IsBINOP() { return false; }

  virtual bool IsMEM() { return false; }

  virtual bool IsCALL() { return false; }

  ~Expression() override = default;
};
}  // namespace IRT
