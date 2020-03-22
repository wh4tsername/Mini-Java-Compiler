#pragma once

#include "ScopeLayer.h"

class ScopeLayerTree {
 public:
  explicit ScopeLayerTree(ScopeLayer* root);
  ScopeLayer* GetRoot();

 private:
  ScopeLayer* root_;
};
