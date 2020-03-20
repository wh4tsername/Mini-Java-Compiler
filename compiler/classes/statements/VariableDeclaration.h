#pragma once

#include "../Type.h"
#include "../expressions/Expression.h"
#include "Statement.h"

class VariableDeclaration : public Statement, public Expression {
 public:
  explicit VariableDeclaration(Type* type, std::string variable_name);

  int Count() final;
  void Run() final;

  void Accept(Visitor* visitor) override;

 private:
  Type* type_;
  std::string variable_name_;
};
