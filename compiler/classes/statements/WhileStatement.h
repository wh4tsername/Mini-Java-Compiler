#pragma once

#include "../expressions/Expression.h"
#include "Statement.h"

class WhileStatement : public Statement {
 public:
  explicit WhileStatement(Expression* expression,
                          Statement* statement);

  void Accept(Visitor* visitor) override;

  Expression* expression_;
  Statement* statement_;
};
