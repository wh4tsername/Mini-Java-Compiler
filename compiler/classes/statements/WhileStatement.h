#pragma once

#include "Statement.h"
#include "../expressions/Expression.h"

class WhileStatement : public Statement {
 public:
  explicit WhileStatement(Expression* expression, Statement* statement);

  void Accept(Visitor* visitor) override;

 private:
  Expression* expression_;
  Statement* statement_;
};
