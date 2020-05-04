#pragma once

#include <string>
#include <vector>

#include "Integer.h"
#include "Object.h"

class Method : public Object {
 public:
  Method(const std::vector<std::string>& argument_names,
         std::string owner_class);

  std::string owner_class_;
  std::vector<Object*> arguments_;
  std::vector<std::string> argument_names_;
};
