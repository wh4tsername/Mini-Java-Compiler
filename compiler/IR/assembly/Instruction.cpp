#include "Instruction.h"

#include <utility>

using namespace IRT;

Instruction::Instruction(std::string cmd, std::vector<Temporary> source_list,
                         std::vector<Temporary> target_list)
    : cmd_(std::move(cmd)),
      source_list_(std::move(source_list)),
      target_list_(std::move(target_list)) {}

std::string Instruction::GetCmd() const { return cmd_; }

std::vector<Temporary> Instruction::GetSources() const { return source_list_; }

std::vector<Temporary> Instruction::GetTargets() const { return target_list_; }

std::ofstream& operator<<(std::ofstream& os, const Instruction& instruction) {
  std::string&& cmd = instruction.GetCmd();
  std::vector<Temporary>&& sources = instruction.GetSources();
  std::vector<Temporary>&& targets = instruction.GetTargets();

  std::string instruction_str(cmd);

  for (size_t i = 0; i < targets.size(); ++i) {
    std::string pattern("t" + std::to_string(i));

    for (size_t pos = instruction_str.find(pattern); pos != std::string::npos;
         pos = instruction_str.find(pattern)) {
      instruction_str.replace(pos, pattern.length(), targets[i].ToString());
    }
  }

  for (size_t i = 0; i < sources.size(); ++i) {
    std::string pattern("s" + std::to_string(i));

    for (size_t pos = instruction_str.find(pattern); pos != std::string::npos;
         pos = instruction_str.find(pattern)) {
      instruction_str.replace(pos, pattern.length(), sources[i].ToString());
    }
  }

  os << instruction_str;

  return os;
}
