#pragma once

#include "expressions/Expression.h"

class Lvalue {
 public:
  explicit Lvalue(Expression* expression);

 private:
  Expression* lvalue_;
};
