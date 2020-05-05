#include "ArrayAccessExpression.h"

ArrayAccessExpression::ArrayAccessExpression(std::string array_indent,
                                             Expression* index_expression)
    : array_indent_(array_indent), index_expression_(index_expression) {}

void ArrayAccessExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
