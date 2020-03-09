#pragma once

#include "../expressions/Expression.h"
#include "Statement.h"

class PrintStatement : public Statement {
 public:
  explicit PrintStatement(Expression* expression);

  void Run() final;

 private:
  Expression* expression_;
};
