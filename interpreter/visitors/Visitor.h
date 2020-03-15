#pragma once

#include "../declarations.h"

class Visitor {
 public:
  virtual void Visit(Expression* expression) = 0;
};
