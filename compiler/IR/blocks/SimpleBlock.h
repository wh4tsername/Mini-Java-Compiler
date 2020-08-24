#pragma once

#include <iostream>

#include "Block.h"

namespace IRT {

class SimpleBlock : public Block {
 public:
  SimpleBlock(Label label, Statement* root, Label next_block_label);

  bool IsSimple() const override;

  Label GetNextBlockLabel() const;

  Block* next_block_;

 private:
  Label next_block_label_;
};

}  // namespace IRT
