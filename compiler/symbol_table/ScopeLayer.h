#pragma once

#include <unordered_map>
#include <vector>

#include "../objects/Object.h"
#include "../objects/UninitObject.h"
#include "Symbol.h"

class ScopeLayer {
 public:
  explicit ScopeLayer(ScopeLayer* parent);
  ScopeLayer();
  void DeclareVariable(const Symbol& symbol);
  void Put(const Symbol& symbol, Object* value);
  Object* Get(const Symbol& symbol);
  bool Has(const Symbol& symbol);

  void AddChild(ScopeLayer* child);

  ScopeLayer* GetChild(size_t index);
  ScopeLayer* GetParent() const;

 private:
  std::unordered_map<Symbol, Object*> values_;
  std::unordered_map<Symbol, size_t> offsets_;
  std::vector<Symbol> symbols_;
  std::string name_;
  ScopeLayer* parent_;
  std::vector<ScopeLayer*> children_;

  ScopeLayer* IterateToRoot(const Symbol& symbol);
};
