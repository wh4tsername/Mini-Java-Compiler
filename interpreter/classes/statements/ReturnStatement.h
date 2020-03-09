#pragma once

#include "../expressions/Expression.h"
#include "Statement.h"

class ReturnStatement : public Statement {
 public:
  explicit ReturnStatement(Expression* expression);

  void Run() final;

 private:
  Expression* expression_;
};
