#include "BlockGraph.h"

using namespace IRT;

BlockGraph::BlockGraph(Block *root) : root_(root), num_tabs_(0) {}

void BlockGraph::Print(const std::string &file_path) {
  num_tabs_ = 0;
  visited_.clear();
  std::ofstream stream(file_path);


  buffer_.emplace_back(root_);
  while (!buffer_.empty()) {
    Block* block = buffer_.front();
    buffer_.pop_front();

    if (block == nullptr || visited_[block]) {
      continue;
    }

    PrintBlock(block, stream);
    visited_[block] = true;

    if (block->IsSimple()) {
      auto simple_block = dynamic_cast<SimpleBlock*>(block);
      buffer_.emplace_back(simple_block->next_block_);
    } else {
      auto conditional_block = dynamic_cast<ConditionalBlock*>(block);
      buffer_.emplace_back(conditional_block->true_block_);
      buffer_.emplace_back(conditional_block->false_block_);
    }
  }

  stream.close();
}

void BlockGraph::PrintBlock(Block *block, std::ofstream &stream) {
  PrintTabs(stream);
  stream << block->GetLabel().ToString() << std::endl;

  if (block->IsSimple()) {
    auto simple_block = dynamic_cast<SimpleBlock *>(block);

    PrintTabs(stream);
    stream << "[next]: " << simple_block->GetNextBlockLabel().ToString()
           << std::endl;
  } else {
    auto conditional_block = dynamic_cast<ConditionalBlock *>(block);

    PrintTabs(stream);
    stream << "[next]: " << conditional_block->GetTrueBlockLabel().ToString()
           << std::endl;

    PrintTabs(stream);
    stream << "[next]: " << conditional_block->GetFalseBlockLabel().ToString()
           << std::endl;
  }

  PrintSeparator(stream);
}

void BlockGraph::PrintTabs(std::ofstream &stream) const {
  for (size_t i = 0; i < num_tabs_; ++i) {
    stream << '\t';
  }
}

void BlockGraph::PrintSeparator(std::ofstream &stream) const {
  PrintTabs(stream);

  for (size_t i = 0; i < SEPARATOR_SIZE_; ++i) {
    stream << '/';
  }

  stream << std::endl;
}
