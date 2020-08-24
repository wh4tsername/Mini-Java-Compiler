#pragma once

#include <unordered_map>

#include "SimpleBlock.h"
#include "ConditionalBlock.h"

namespace IRT {

class BlockGraph {
 public:
  explicit BlockGraph(Block* root);

 private:
  Block* root_;

  std::unordered_map<Block*, bool> visited_;
};

}
