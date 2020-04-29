#include "Function.h"

Function::Function(const std::vector<std::string>& argument_names)
    : argument_names_(argument_names) {
  for (const std::string& name : argument_names) {
    arguments_.push_back(new Integer(0));
  }
}
