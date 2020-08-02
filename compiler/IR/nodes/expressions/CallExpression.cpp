#include "CallExpression.h"

void IRT::CallExpression::Accept(IRT::Visitor *visitor) {
  visitor->Visit(this);
}

IRT::CallExpression::CallExpression(Expression *expression,
                                    ExpressionList *args)
    : function_name_(expression), args_(args) {}
