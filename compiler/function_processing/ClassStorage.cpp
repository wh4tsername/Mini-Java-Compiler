#include "ClassStorage.h"

ClassStorage& ClassStorage::GetInstance() {
  static ClassStorage storage;
  return storage;
}

void ClassStorage::SetMethod(
    const Symbol& symbol,
    std::unordered_map<Symbol, std::shared_ptr<Method>> methods) {
  class_methods_[symbol] = std::move(methods);
}

void ClassStorage::SetField(
    const Symbol& symbol,
    std::unordered_map<Symbol, std::shared_ptr<PrimitiveObject>> fields) {
  class_fields_[symbol] = std::move(fields);
}

std::unordered_map<Symbol, std::shared_ptr<Method>>
ClassStorage::GetMethods(const Symbol& symbol) const {
  if (class_methods_.find(symbol) != class_methods_.end()) {
    return class_methods_.at(symbol);
  } else {
    throw std::runtime_error("Class not found");
  }
}

std::unordered_map<Symbol, std::shared_ptr<PrimitiveObject>>
ClassStorage::GetFields(const Symbol& symbol) const {
  if (class_fields_.find(symbol) != class_fields_.end()) {
    return class_fields_.at(symbol);
  } else {
    throw std::runtime_error("Class not found");
  }
}

std::vector<Symbol> ClassStorage::GetMethodsNames(const Symbol& symbol) {
  return class_methods_names_[symbol];
}

void ClassStorage::SetClassMethodsNames(
    const Symbol& symbol, std::vector<Symbol> class_methods_names) {
  class_methods_names_[symbol] = std::move(class_methods_names);
}

std::vector<Symbol> ClassStorage::GetFieldsNames(const Symbol& symbol) {
  return class_fields_names_[symbol];
}

void ClassStorage::SetClassFieldsNames(const Symbol& symbol,
                                       std::vector<Symbol> class_fields_names) {
  class_fields_names_[symbol] = std::move(class_fields_names);
}
