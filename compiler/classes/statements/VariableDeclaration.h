#pragma once

#include "../Type.h"
#include "../expressions/Expression.h"
#include "Statement.h"

class VariableDeclaration : public Statement, public Expression {
 public:
  explicit VariableDeclaration(Type* type, std::string variable_name);

  void Accept(Visitor* visitor) override;

  Type* type_;
  std::string variable_name_;
};
