#include "ScopeLayer.h"

ScopeLayer::ScopeLayer(ScopeLayer* parent) : parent_(parent) {
  parent_->AddChild(this);
}

ScopeLayer::ScopeLayer() : parent_(nullptr) {}

void ScopeLayer::DeclareVariable(const Symbol& symbol) {
  if (values_.find(symbol) != values_.end()) {
    throw std::runtime_error("Variable has already been declared");
  }

  values_[symbol] = new UninitObject;
  offsets_[symbol] = symbols_.size();
  symbols_.emplace_back(symbol);
}

ScopeLayer* ScopeLayer::IterateToRoot(const Symbol& symbol) {
  ScopeLayer* current_layer = this;

  while (!current_layer->Has(symbol) && current_layer->parent_ != nullptr) {
    current_layer = current_layer->parent_;
  }

  return current_layer;
}

void ScopeLayer::Put(const Symbol& symbol, Object* value) {
  ScopeLayer* current_layer = IterateToRoot(symbol);

  if (current_layer->Has(symbol)) {
    current_layer->values_.find(symbol)->second = value;
  } else {
    throw std::runtime_error("Undeclared variable");
  }
}

Object* ScopeLayer::Get(const Symbol& symbol) {
  ScopeLayer* current_layer = IterateToRoot(symbol);

  if (current_layer->Has(symbol)) {
    return current_layer->values_.find(symbol)->second;
  } else {
    throw std::runtime_error("Undeclared variable");
  }
}

bool ScopeLayer::Has(const Symbol& symbol) {
  return values_.find(symbol) != values_.end();
}

ScopeLayer* ScopeLayer::GetChild(size_t index) { return children_[index]; }

void ScopeLayer::AddChild(ScopeLayer* child) { children_.emplace_back(child); }

ScopeLayer* ScopeLayer::GetParent() const { return parent_; }
