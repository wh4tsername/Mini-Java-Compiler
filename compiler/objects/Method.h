#pragma once

#include <string>
#include <vector>

#include "Integer.h"
#include "Object.h"

class Method : public Object {
 public:
  Method(const std::vector<std::pair<std::string, std::string>>& args,
         std::string owner_class, std::string return_type);

  std::string return_type_;
  std::string owner_class_;
  std::vector<Object*> arguments_;
  std::vector<std::string> argument_names_;
  std::vector<std::string> types_;
};
