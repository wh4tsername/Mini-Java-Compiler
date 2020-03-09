#pragma once

#include "Statement.h"

#include <vector>

class ListOfStatements : public Statement {
 public:
  void AddStatement(Statement* statement);

  void Run() final;

 private:
  std::vector<Statement*> list_of_statements_;
};
