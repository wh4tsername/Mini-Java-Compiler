#pragma once

#include <vector>

#include "Expression.h"
#include "../../visitors/Node.h"

class MethodExpression : public Node {
 public:
  explicit MethodExpression(Expression* init_expression);

  void AddExpression(Expression* expression);

  void Accept(Visitor* visitor) override;

 private:
  std::vector<Expression*> list_of_expressions_;
};
