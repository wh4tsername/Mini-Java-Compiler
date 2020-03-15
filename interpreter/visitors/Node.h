#pragma once

#include "Visitor.h"

class Node {
 public:
  virtual void Accept(Visitor* visitor) = 0;

  virtual ~Node() = default;
};
