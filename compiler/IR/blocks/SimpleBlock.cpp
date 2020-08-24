#include "SimpleBlock.h"

#include <utility>

using namespace IRT;

SimpleBlock::SimpleBlock(Label label, Statement *root, Label next_block_label)
    : Block(std::move(label), root),
      next_block_label_(std::move(next_block_label)),
      next_block_(nullptr) {}

bool SimpleBlock::IsSimple() const { return true; }

Label SimpleBlock::GetNextBlockLabel() const { return next_block_label_; }
