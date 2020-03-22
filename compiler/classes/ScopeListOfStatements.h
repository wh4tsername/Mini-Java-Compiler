#pragma once

#include "statements/Statement.h"
#include "statements/ListOfStatements.h"

class ScopeListOfStatements : public Statement {
 public:
  explicit ScopeListOfStatements(ListOfStatements* list_of_statements);
  void Accept(Visitor* visitor) override;

  ListOfStatements* list_of_statements_;
};
