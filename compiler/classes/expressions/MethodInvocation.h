#pragma once

#include <string>

#include "Expression.h"
#include "../statements/Statement.h"
#include "MethodExpression.h"

class MethodInvocation : public Expression, public Statement {
 public:
  explicit MethodInvocation(Expression* call_from, std::string method_name,
                            MethodExpression* arguments_list);

  void Accept(Visitor* visitor) override;

 private:
  Expression* call_from_;
  std::string method_name_;
  MethodExpression* arguments_list_;
};
