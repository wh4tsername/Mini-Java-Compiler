#include "MethodInvocation.h"

MethodInvocation::MethodInvocation(std::string call_from,
                                   std::string method_name,
                                   MethodExpression* arguments_list)
    : call_from_(std::move(call_from)),
      method_name_(std::move(method_name)),
      arguments_list_(arguments_list) {}

void MethodInvocation::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
