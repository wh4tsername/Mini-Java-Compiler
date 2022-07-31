#include "Block.h"

#include <utility>

using namespace IRT;

Block::Block(Label label, Statement *root)
    : label_(std::move(label)), root_(root) {}

Label Block::GetLabel() const { return label_; }
