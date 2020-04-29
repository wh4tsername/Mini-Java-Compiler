#pragma once

#include <vector>
#include <string>

#include "Object.h"
#include "Integer.h"

class Function : public Object {
 public:
  Function(const std::vector<std::string>& argument_names);

  std::vector<Object*> arguments_;
  std::vector<std::string> argument_names_;
};
