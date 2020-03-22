#include "ScopeLayerTree.h"

ScopeLayerTree::ScopeLayerTree(ScopeLayer* root) : root_(root) {}

ScopeLayer* ScopeLayerTree::GetRoot() { return root_; }
