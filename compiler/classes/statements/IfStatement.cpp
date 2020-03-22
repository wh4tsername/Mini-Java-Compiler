#include "IfStatement.h"

IfStatement::IfStatement(Expression* expression, Statement* if_statement,
                         Statement* else_statement)
    : expression_(expression),
      if_statement_(if_statement),
      else_statement_(else_statement) {}

void IfStatement::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
