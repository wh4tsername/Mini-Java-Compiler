#pragma once

#include "../../visitors/Node.h"

class Statement : public Node {
 public:
  virtual void Run() = 0;
};
