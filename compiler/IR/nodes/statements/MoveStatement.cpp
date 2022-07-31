#include "MoveStatement.h"

using namespace IRT;

MoveStatement::MoveStatement(Expression *source, Expression *target)
    : source_(source), target_(target) {}

void MoveStatement::Accept(Visitor *visitor) { visitor->Visit(this); }
