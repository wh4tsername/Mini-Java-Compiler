#include "ScopeLayer.h"

#include "../objects/Function.h"
#include "../objects/Integer.h"
#include "../objects/UninitObject.h"

#include <iostream>
#include <utility>

ScopeLayer::ScopeLayer(ScopeLayer* parent) : parent_(parent) {
  std::cout << "Constructor called" << std::endl;
  std::cout << "End contstructor called" << std::endl;

  parent_->AddChild(this);
}

void ScopeLayer::AttachParent() {}

ScopeLayer::ScopeLayer() : parent_(nullptr) {}

void ScopeLayer::DeclareVariable(const Symbol& symbol) {
  if (values_.find(symbol) != values_.end()) {
    throw std::runtime_error("Variable has declared");
  }

  values_[symbol] = std::make_shared<Integer>(0);
  offsets_[symbol] = symbols_.size();
  symbols_.push_back(symbol);
}

void ScopeLayer::DeclareFunction(const Symbol& symbol,
                                 MethodDeclaration* function) {
  if (values_.find(symbol) != values_.end()) {
    throw std::runtime_error("Variable has declared");
  }

  // TODO(@wh4tsername) Type checking

  std::vector<std::string> args;
  for (const auto& parameter : function->formals_->formals_) {
    args.emplace_back(parameter.second);
  }

  values_[symbol] = std::make_shared<Function>(args);
}

void ScopeLayer::Put(const Symbol& symbol, std::shared_ptr<Object> value) {
  ScopeLayer* current_layer = this;

  while (!current_layer->Has(symbol) && current_layer->parent_ != nullptr) {
    current_layer = current_layer->parent_;
  }
  if (current_layer->Has(symbol)) {
    current_layer->values_.find(symbol)->second = std::move(value);
  } else {
    throw std::runtime_error("Variable not declared");
  }
}

bool ScopeLayer::Has(const Symbol& symbol) {
  return values_.find(symbol) != values_.end();
}

std::shared_ptr<Object> ScopeLayer::Get(const Symbol& symbol) {
  ScopeLayer* current_layer = this;

  while (!current_layer->Has(symbol) && current_layer->parent_ != nullptr) {
    current_layer = current_layer->parent_;
  }
  if (current_layer->Has(symbol)) {
    return current_layer->values_.find(symbol)->second;
  } else {
    throw std::runtime_error("Variable not declared");
  }
}

ScopeLayer* ScopeLayer::GetChild(size_t index) {
  std::cout << "Children of scope: " << children_.size() << std::endl;
  return children_[index];
}

void ScopeLayer::AddChild(ScopeLayer* child) { children_.push_back(child); }

ScopeLayer* ScopeLayer::GetParent() const { return parent_; }

ScopeLayer::~ScopeLayer() {
  for (ScopeLayer* layer : children_) {
    delete layer;
  }
}

void ScopeLayer::PrintLayer(std::ostream& stream, int num_tabs) const {
  for (auto&& symbol : symbols_) {
    for (int i = 0; i < num_tabs; ++i) {
      stream << "\t";
    }
    stream << symbol.GetName() << std::endl;
  }
  for (ScopeLayer* layer : children_) {
    layer->PrintLayer(stream, num_tabs + 1);
  }
}
