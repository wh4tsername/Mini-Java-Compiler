#pragma once

#include "expressions/Expression.h"
#include "../visitors/Node.h"

class Lvalue : public Node {
 public:
  explicit Lvalue(Expression* expression);

  void Accept(Visitor* visitor) override;

 private:
  Expression* lvalue_;
};
