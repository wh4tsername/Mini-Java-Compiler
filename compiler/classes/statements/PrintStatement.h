#pragma once

#include "../expressions/Expression.h"
#include "Statement.h"

class PrintStatement : public Statement {
 public:
  explicit PrintStatement(Expression* expression);

  void Accept(Visitor* visitor) override;

 private:
  Expression* expression_;
};
