#include "SeqStatement.h"

using namespace IRT;

SeqStatement::SeqStatement(Statement* first, Statement* second)
    : first_statement_(first), second_statement_(second) {}

void SeqStatement::Accept(Visitor* visitor) { visitor->Visit(this); }

bool SeqStatement::IsSeq() { return true; }
