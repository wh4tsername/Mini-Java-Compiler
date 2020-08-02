#include "ExpStatement.h"

using namespace IRT;

ExpStatement::ExpStatement(Expression* expression) : expression_(expression) {}

void ExpStatement::Accept(Visitor* visitor) { visitor->Visit(this); }

bool ExpStatement::IsExp() { return true; }
