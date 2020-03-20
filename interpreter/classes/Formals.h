#pragma once

#include "Type.h"
#include "../visitors/Node.h"

#include <algorithm>
#include <vector>

class Formals : public Node {
 public:
  void AddFormal(Type* type, const std::string& arg_name);

  void Accept(Visitor* visitor) override;

 private:
  std::vector<std::pair<Type*, std::string>> formals_;
};
