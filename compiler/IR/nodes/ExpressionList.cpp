#include "ExpressionList.h"

namespace IRT {
void ExpressionList::Accept(Visitor* visitor) { visitor->Visit(this); }

void ExpressionList::Add(Expression* expression) {
  expressions_.emplace_back(expression);
}
}  // namespace IRT
