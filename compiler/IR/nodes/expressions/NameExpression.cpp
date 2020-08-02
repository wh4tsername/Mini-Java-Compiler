#include "NameExpression.h"

namespace IRT {
NameExpression::NameExpression(Label label) : label_(label) {}

bool NameExpression::IsNAME() { return true; }

void NameExpression::Accept(Visitor* visitor) { visitor->Visit(this); }
}  // namespace IRT
