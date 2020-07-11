#pragma once

#include <string>
#include <vector>

#include "../classes/Type.h"
#include "../classes/statements/MethodDeclaration.h"
#include "Object.h"

class Method : public Object {
 public:
  explicit Method(MethodDeclaration* method_declaration);

  void SetOwner(std::string owner_class);
  void SetArgsNames(std::vector<std::string> args_names);
  void SetArgsTypes(std::vector<std::string> args_types);

  std::string GetTypename() override;

  size_t GetParamsNumber();

  MethodDeclaration* method_declaration_;
  Type* return_value_type_;

  std::string owner_class_;
  std::vector<std::string> args_names_;
  std::vector<std::string> args_types_;
};
