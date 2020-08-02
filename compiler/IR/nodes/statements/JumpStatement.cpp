#include "JumpStatement.h"

using namespace IRT;

JumpStatement::JumpStatement(Label label) : label_(label) {}

void JumpStatement::Accept(Visitor* visitor) { visitor->Visit(this); }
