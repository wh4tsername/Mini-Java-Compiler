#pragma once

#include <cstdint>
#include <string>

class Object {
 public:
  virtual std::string GetTypename() = 0;
  virtual ~Object() = default;
};
