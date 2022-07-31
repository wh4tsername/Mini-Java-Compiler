#pragma once

#include <map>
#include <fstream>
#include <deque>

#include "SimpleBlock.h"
#include "ConditionalBlock.h"

namespace IRT {

class BlockGraph {
 public:
  explicit BlockGraph(Block* root);

  void Print(const std::string& file_path);

 private:
  void PrintBlock(Block* block, std::ofstream& stream);
  void PrintTabs(std::ofstream& stream) const;
  void PrintSeparator(std::ofstream& stream) const;

  Block* root_;
  std::map<Block*, bool> visited_;
  std::deque<Block*> buffer_;

  size_t num_tabs_;
  const size_t SEPARATOR_SIZE_ = 20;
};

}
