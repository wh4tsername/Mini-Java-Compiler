#include "ListOfStatements.h"

void ListOfStatements::AddStatement(Statement* statement) {
  list_of_statements_.emplace_back(statement);
}

void ListOfStatements::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
