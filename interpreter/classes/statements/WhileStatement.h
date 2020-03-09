#pragma once

#include "Statement.h"
#include "../expressions/Expression.h"

class WhileStatement : public Statement {
 public:
  explicit WhileStatement(Expression* expression, Statement* statement);

  void Run() final;

 private:
  Expression* expression_;
  Statement* statement_;
};
