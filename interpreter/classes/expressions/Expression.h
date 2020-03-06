#pragma once

#include "../errors.h"

class Expression {
 public:
  virtual int Count() { return 0; };
};