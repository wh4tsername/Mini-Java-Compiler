#pragma once

#include "../generators/Label.h"
#include "../nodes/statements/Statement.h"

namespace IRT {

class Block {
 public:
  Block(Label label, Statement* root);

  virtual bool IsSimple() const = 0;

  Label GetLabel() const;

 protected:
  Label label_;
  Statement* root_;
};

}  // namespace IRT
