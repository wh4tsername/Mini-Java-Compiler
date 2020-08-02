#include "BinopExpression.h"

void IRT::BinopExpression::Accept(IRT::Visitor *visitor) {
  visitor->Visit(this);
}

IRT::BinopExpression::BinopExpression(BinaryOperatorType type, Expression *lhs,
                                      Expression *rhs)
    : type_(type), lhs_(lhs), rhs_(rhs) {}
