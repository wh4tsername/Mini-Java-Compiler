#pragma once

#include "Statement.h"

#include <vector>

class ListOfStatements : public Statement {
 public:
  void AddStatement(Statement* statement);

  void Accept(Visitor* visitor) override;
  void PreAccept(Visitor* visitor) override;

  std::vector<Statement*> list_of_statements_;
};
