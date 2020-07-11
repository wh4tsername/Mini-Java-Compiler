#pragma once

#include <memory>
#include <unordered_map>

#include "../classes/statements/ClassDeclaration.h"
#include "../symbol_table/Symbol.h"
#include "Method.h"
#include "Object.h"
#include "PrimitiveObject.h"

class Class : public Object {
 public:
  explicit Class(ClassDeclaration* class_declaration);

  void AddMethod(const Symbol& symbol, std::shared_ptr<Method> method);
  void AddField(const Symbol& symbol, std::shared_ptr<PrimitiveObject> field);

  std::string GetTypename() override;

  ClassDeclaration* class_declaration_;
  std::vector<Symbol> method_symbols_;
  std::vector<Symbol> field_symbols_;
  std::unordered_map<Symbol, std::shared_ptr<Method>> method_objects_;
  std::unordered_map<Symbol, std::shared_ptr<PrimitiveObject>> field_objects_;
};
