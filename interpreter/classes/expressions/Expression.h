#pragma once

#include "../errors.h"
#include "../../visitors/Node.h"

class Expression {
 public:
  virtual int Count() { return 0; };
};