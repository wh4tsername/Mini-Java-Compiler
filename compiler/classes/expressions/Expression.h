#pragma once

#include "../errors.h"
#include "../../visitors/Node.h"

class Expression : public Node {
 public:
  virtual int Count() { return 0; };
};