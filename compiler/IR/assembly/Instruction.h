#pragma once

#include "../generators/Temporary.h"

#include <fstream>
#include <vector>

namespace IRT {

class Instruction {
 public:
  Instruction(std::string cmd, std::vector<Temporary> source_list,
              std::vector<Temporary> target_list);

  std::string GetCmd() const;
  std::vector<Temporary> GetSources() const;
  std::vector<Temporary> GetTargets() const;

 private:
  std::string cmd_;
  std::vector<Temporary> source_list_;
  std::vector<Temporary> target_list_;
};

}  // namespace IRT

std::ofstream& operator<<(std::ofstream& os, const IRT::Instruction& instruction);
