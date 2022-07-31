#include "EseqExpression.h"

IRT::EseqExpression::EseqExpression(Statement *statement,
                                    Expression *expression)
    : statement_(statement), expression_(expression) {}

bool IRT::EseqExpression::IsESEQ() { return true; }

void IRT::EseqExpression::Accept(Visitor *visitor) { visitor->Visit(this); }
