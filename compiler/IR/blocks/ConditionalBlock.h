#pragma once

#include "Block.h"

namespace IRT {

class ConditionalBlock : public Block {
 public:
  ConditionalBlock(Label label, Statement* root, Label true_block_label,
                   Label false_block_label);

  bool IsSimple() const override;

  Label GetTrueBlockLabel() const;
  Label GetFalseBlockLabel() const;

  Block* true_block_;
  Block* false_block_;

 private:
  Label true_block_label_;
  Label false_block_label_;
};

}  // namespace IRT
