#include "ScopeListOfStatements.h"

ScopeListOfStatements::ScopeListOfStatements(
    ListOfStatements* list_of_statements)
    : list_of_statements_(list_of_statements) {}

void ScopeListOfStatements::Accept(Visitor* visitor) { visitor->Visit(this); }
