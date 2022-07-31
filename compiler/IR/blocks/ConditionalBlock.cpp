#include "ConditionalBlock.h"

#include <utility>

using namespace IRT;

ConditionalBlock::ConditionalBlock(Label label, Statement *root,
                                   Label true_block_label,
                                   Label false_block_label)
    : Block(std::move(label), root),
      true_block_label_(std::move(true_block_label)),
      false_block_label_(std::move(false_block_label)),
      true_block_(nullptr),
      false_block_(nullptr) {}

bool ConditionalBlock::IsSimple() const { return false; }

Label ConditionalBlock::GetTrueBlockLabel() const { return true_block_label_; }

Label ConditionalBlock::GetFalseBlockLabel() const {
  return false_block_label_;
}
