#pragma once

#include "ScopeLayer.h"

#include <fstream>
#include <unordered_map>

class ScopeLayerTree {
 public:
  explicit ScopeLayerTree(ScopeLayer* root);
  ScopeLayerTree(const ScopeLayerTree &other);
  void PrintTree(const std::string& filename);

  std::shared_ptr<Object> Get(const Symbol& symbol);
  ScopeLayer* root_;
  ~ScopeLayerTree();

  /**
   * Adds mapping from named scope for fast access
   * @param name - name of layer - function name
   * @param layer - scope layer to use
   */
  void AddMapping(const Symbol& name, ScopeLayer* layer);

  /**
   * Get function by name
   * @param name
   * @return Function scope
   */
  ScopeLayer* GetFunctionScope(const Symbol& name);

 private:
  std::ofstream stream_;
  std::unordered_map<Symbol, ScopeLayer*> layer_mapping_;

};