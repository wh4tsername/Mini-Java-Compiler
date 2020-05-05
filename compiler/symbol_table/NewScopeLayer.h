#pragma once

#include <iostream>
#include <memory>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>

#include "../classes/Type.h"
#include "../objects/Integer.h"
#include "../objects/Method.h"
#include "../objects/UninitObject.h"
#include "Symbol.h"

class NewScopeLayer {
 public:
  NewScopeLayer();
  NewScopeLayer(NewScopeLayer* parent, std::string name,
                const Symbol& class_symbol);

  void AddChild(NewScopeLayer* child);

  bool HasVariable(const Symbol& symbol);
  std::shared_ptr<Object> GetVariable(const Symbol& symbol);

  bool HasArray(const Symbol& symbol);
  std::vector<std::shared_ptr<Object>>& GetArray(const Symbol& symbol);

  void DeclareVariable(Type* type, const Symbol& symbol);

  std::string name_;
  NewScopeLayer* parent_;
  std::vector<NewScopeLayer*> children_;

  Symbol class_symbol_;

  std::unordered_map<Symbol, std::shared_ptr<Object>> variables_;
  std::unordered_map<Symbol, std::vector<std::shared_ptr<Object>>> arrays_;

  // pre type checking
  std::unordered_map<Symbol, std::string> user_type_system;
};
