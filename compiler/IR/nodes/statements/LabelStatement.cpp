#include "LabelStatement.h"

using namespace IRT;

LabelStatement::LabelStatement(IRT::Label label) : label_(label) {}

void LabelStatement::Accept(Visitor* visitor) { visitor->Visit(this); }
