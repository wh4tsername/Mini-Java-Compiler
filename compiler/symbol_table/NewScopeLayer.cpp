#include "NewScopeLayer.h"

NewScopeLayer::NewScopeLayer() : parent_(nullptr), name_("GLOBAL") {}

NewScopeLayer::NewScopeLayer(NewScopeLayer* parent, std::string name)
    : parent_(parent), name_(std::move(name)) {
  parent_->AddChild(this);
}

void NewScopeLayer::AddChild(NewScopeLayer* child) {
  children_.emplace_back(child);
}

bool NewScopeLayer::HasVariable(const Symbol& symbol) {
  return variables_.find(symbol) != variables_.end();
}

std::shared_ptr<Object> NewScopeLayer::GetVariable(const Symbol& symbol) {
  NewScopeLayer* current = this;

  while (!current->HasVariable(symbol) && current->parent_ == nullptr) {
    current = current->parent_;
  }

  if (current->parent_ == nullptr) {
    throw std::runtime_error("Variable " + symbol.GetName() +
                             " is not declared");
  }

  return current->variables_[symbol];
}

bool NewScopeLayer::HasArray(const Symbol& symbol) {
  return arrays_.find(symbol) != arrays_.end();
}

std::vector<std::shared_ptr<Object>>& NewScopeLayer::GetArray(
    const Symbol& symbol) {
  NewScopeLayer* current = this;

  while (!current->HasArray(symbol) && current->parent_ == nullptr) {
    current = current->parent_;
  }

  if (current->parent_ == nullptr) {
    throw std::runtime_error("Array " + symbol.GetName() + " is not declared");
  }

  return current->arrays_[symbol];
}

void NewScopeLayer::DeclareVariable(Type* type, const Symbol& symbol) {
  if (type->type_name_.back() != ']') {
    if (HasVariable(symbol)) {
      throw std::runtime_error("Variable " + symbol.GetName() +
          " has been already declared!");
    }

    variables_[symbol] = std::make_shared<UninitObject>();
  } else {
    if (HasArray(symbol)) {
      throw std::runtime_error("Array " + symbol.GetName() +
          " has been already declared!");
    }

    arrays_[symbol] = std::vector<std::shared_ptr<Object>>();
  }
}
