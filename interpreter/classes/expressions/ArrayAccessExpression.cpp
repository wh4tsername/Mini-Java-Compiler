#include "ArrayAccessExpression.h"

ArrayAccessExpression::ArrayAccessExpression(Expression* main_expression,
                                             Expression* index_expression)
    : main_expression_(main_expression), index_expression_(index_expression) {}

int ArrayAccessExpression::Count() { return 0; }
