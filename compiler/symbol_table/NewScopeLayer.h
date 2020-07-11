#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "../classes/Type.h"
#include "../objects/Method.h"
#include "Symbol.h"
#include "../objects/PrimitiveSimpleObject.h"
#include "../objects/PrimitiveArrayObject.h"

class NewScopeLayer {
 public:
  NewScopeLayer();
  NewScopeLayer(NewScopeLayer* parent, std::string name,
                const Symbol& class_symbol, const Symbol& method_symbol);

  void AddChild(NewScopeLayer* child);
  void PrepareTraversing();

  bool HasVariable(const Symbol& symbol);
  NewScopeLayer* GetVariableLayer(const Symbol& symbol);

  bool HasArray(const Symbol& symbol);
  NewScopeLayer* GetArrayLayer(const Symbol& symbol);

  void DeclareVariable(Type* type, const Symbol& symbol);

  std::string name_;
  NewScopeLayer* parent_;
  std::vector<NewScopeLayer*> children_;

  Symbol class_symbol_;
  Symbol method_symbol_;

  int traverse_index;

  std::unordered_map<Symbol, std::shared_ptr<PrimitiveObject>> variables_;
  std::unordered_map<Symbol, std::shared_ptr<PrimitiveObject>> arrays_;

  // pre type checking
  std::unordered_map<Symbol, std::string> user_type_system_;

  // type checking
  std::unordered_map<Symbol, int> symbol_types_;
};
