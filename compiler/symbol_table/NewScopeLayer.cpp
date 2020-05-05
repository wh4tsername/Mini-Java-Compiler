#include "NewScopeLayer.h"

NewScopeLayer::NewScopeLayer()
    : parent_(nullptr), name_("__GLOBAL__"), class_symbol_() {}

NewScopeLayer::NewScopeLayer(NewScopeLayer* parent, std::string name,
                             const Symbol& class_symbol)
    : parent_(parent), name_(std::move(name)), class_symbol_(class_symbol) {
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

  while (!current->HasVariable(symbol) &&
         current->parent_->parent_ != nullptr) {
    current = current->parent_;
  }

  if (current->HasVariable(symbol)) {
    return current->variables_[symbol];
  }

  throw std::runtime_error("Variable " + symbol.GetName() + " is not declared");
}

bool NewScopeLayer::HasArray(const Symbol& symbol) {
  return arrays_.find(symbol) != arrays_.end();
}

std::vector<std::shared_ptr<Object>>& NewScopeLayer::GetArray(
    const Symbol& symbol) {
  NewScopeLayer* current = this;

  while (!current->HasArray(symbol) && current->parent_->parent_ != nullptr) {
    current = current->parent_;
  }

  if (current->HasArray(symbol)) {
    return current->arrays_[symbol];
  }

  throw std::runtime_error("Array " + symbol.GetName() + " is not declared");
}

void NewScopeLayer::DeclareVariable(Type* type, const Symbol& symbol) {
  // check duplicates of var names for var and array
  if (HasVariable(symbol)) {
    throw std::runtime_error("Variable " + symbol.GetName() +
        " has been already declared!");
  }
  if (HasArray(symbol)) {
    throw std::runtime_error("Array " + symbol.GetName() +
        " has been already declared!");
  }

  if (type->type_name_.back() != ']') {
    variables_[symbol] = std::make_shared<UninitObject>();
  } else {
    arrays_[symbol] = std::vector<std::shared_ptr<Object>>();
  }
}
