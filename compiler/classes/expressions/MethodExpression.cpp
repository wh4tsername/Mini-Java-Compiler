#include "MethodExpression.h"

MethodExpression::MethodExpression(Expression* init_expression) {
  list_of_expressions_.emplace_back(init_expression);
}

void MethodExpression::AddExpression(Expression* expression) {
  list_of_expressions_.emplace_back(expression);
}

void MethodExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
