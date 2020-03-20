#include "Lvalue.h"

Lvalue::Lvalue(Expression* expression) { lvalue_ = expression; }

void Lvalue::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
