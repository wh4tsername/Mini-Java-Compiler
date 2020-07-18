#include "Method.h"

Method::Method(MethodDeclaration* method_declaration)
    : method_declaration_(method_declaration),
      return_value_type_(method_declaration->type_) {}

std::string Method::GetTypename() {
  return "method, return type: " + return_value_type_->type_name_;
}

size_t Method::GetParamsNumber() {
  if (method_declaration_->formals_) {
    return method_declaration_->formals_->formals_.size();
  }
  return 0;
}

void Method::SetOwner(std::string owner_class) {
  owner_class_ = std::move(owner_class);
}

void Method::SetArgsNames(std::vector<std::string> args_names) {
  args_names_ = std::move(args_names);
}

void Method::SetArgsTypes(std::vector<std::string> args_types) {
  args_types_ = std::move(args_types);
}
