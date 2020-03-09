#pragma once

#include "Type.h"

#include <algorithm>
#include <vector>

class Formals {
 public:
  void AddFormal(Type* type, const std::string& arg_name);

 private:
  std::vector<std::pair<Type*, std::string>> formals_;
};
