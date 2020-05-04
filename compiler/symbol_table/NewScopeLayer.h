#pragma once

#include <iostream>
#include <utility>
#include <string>
#include <unordered_map>
#include <memory>

#include "../objects/Method.h"
#include "../objects/Integer.h"
#include "../objects/UninitObject.h"
#include "../classes/Type.h"
#include "Symbol.h"

class NewScopeLayer {
 public:
  NewScopeLayer();
  NewScopeLayer(NewScopeLayer* parent, std::string name);

  void AddChild(NewScopeLayer* child);

  bool HasVariable(const Symbol& symbol);
  std::shared_ptr<Object> GetVariable(const Symbol& symbol);

  bool HasArray(const Symbol& symbol);
  std::vector<std::shared_ptr<Object>>& GetArray(const Symbol& symbol);

  void DeclareVariable(Type* type, const Symbol& symbol);

  std::string name_;
  NewScopeLayer* parent_;
  std::vector<NewScopeLayer*> children_;

  std::unordered_map<Symbol, std::shared_ptr<Object>> variables_;
  std::unordered_map<Symbol, std::vector<std::shared_ptr<Object>>> arrays_;
};
