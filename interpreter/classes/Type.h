#pragma once

#include <string>

class Type {
 public:
  explicit Type(std::string type_name);

  std::string GetType();

 private:
  std::string type_name_;
};
