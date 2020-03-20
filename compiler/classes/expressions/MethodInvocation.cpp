#include "MethodInvocation.h"

MethodInvocation::MethodInvocation(Expression* call_from,
                                   std::string method_name,
                                   MethodExpression* arguments_list)
    : call_from_(call_from),
      method_name_(std::move(method_name)),
      arguments_list_(arguments_list) {}

int MethodInvocation::Count() { return 0; }

void MethodInvocation::Run() {}

void MethodInvocation::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
