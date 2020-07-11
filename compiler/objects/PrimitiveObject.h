#pragma once

#include "Object.h"

class PrimitiveObject : public Object {
 public:
  virtual std::size_t GetSize() = 0;
  virtual bool IsArray() = 0;
  std::string GetTypename() = 0;
};
