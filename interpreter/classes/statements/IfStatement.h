#pragma once

#include "../expressions/Expression.h"
#include "Statement.h"

class IfStatement : public Statement {
 public:
  explicit IfStatement(Expression* expression, Statement* if_statement,
                       Statement* else_statement);

  void Run() final;

 private:
  Expression* expression_;
  Statement* if_statement_;
  Statement* else_statement_;
};
