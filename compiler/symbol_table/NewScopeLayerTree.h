#pragma once

#include <unordered_map>

#include "../classes/statements/MethodDeclaration.h"
#include "../classes/statements/VariableDeclaration.h"
#include "NewScopeLayer.h"
#include "Symbol.h"

class NewScopeLayerTree {
 public:
  using table_t = std::unordered_map<
      Symbol, std::tuple<std::unordered_map<Symbol, std::shared_ptr<Object>>,
                         std::unordered_map<Symbol, std::shared_ptr<Method>>,
                         std::unordered_map<
                             Symbol, std::vector<std::shared_ptr<Object>>>>>;

  explicit NewScopeLayerTree(NewScopeLayer* layer);

  NewScopeLayer* root_;

  table_t class_symbols_table_;
};
