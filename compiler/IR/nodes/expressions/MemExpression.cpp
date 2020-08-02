#include "MemExpression.h"

using namespace IRT;
void MemExpression::Accept(Visitor* visitor) { visitor->Visit(this); }

MemExpression::MemExpression(Expression* expression)
    : expression_(expression) {}
