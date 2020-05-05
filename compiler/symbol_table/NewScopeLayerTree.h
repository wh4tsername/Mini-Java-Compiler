#pragma once

#include <unordered_map>

#include "../classes/statements/MethodDeclaration.h"
#include "../classes/statements/VariableDeclaration.h"
#include "NewScopeLayer.h"
#include "Symbol.h"

class NewScopeLayerTree {
 public:
  using var_t = std::pair<std::string, std::shared_ptr<Object>>;
  using arr_t = std::pair<std::string, std::vector<std::shared_ptr<Object>>>;
  // 0 - var field
  // 1 - method
  // 2 - arr field
  using symbol_table_t = std::unordered_map<
      Symbol, std::tuple<std::unordered_map<Symbol, var_t>,
                         std::unordered_map<Symbol, std::shared_ptr<Method>>,
                         std::unordered_map<
                             Symbol, arr_t>>>;

  using member_table_t = std::unordered_map<Symbol, std::unordered_set<Symbol>>;

  explicit NewScopeLayerTree(NewScopeLayer* layer);

  NewScopeLayer* root_;

  symbol_table_t class_symbols_table_;
  member_table_t class_members_table_;
};
