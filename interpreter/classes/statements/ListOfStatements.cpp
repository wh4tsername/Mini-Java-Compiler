#include "ListOfStatements.h"

void ListOfStatements::AddStatement(Statement* statement) {
  list_of_statements_.emplace_back(statement);
}

void ListOfStatements::Run() {
  for (auto&& statement : list_of_statements_) {
    statement->Run();
  }
}
