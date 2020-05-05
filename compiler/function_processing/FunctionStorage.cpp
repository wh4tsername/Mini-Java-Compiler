#include "FunctionStorage.h"

FunctionStorage& FunctionStorage::GetInstance() {
  static FunctionStorage storage;

  return storage;
}

void FunctionStorage::Set(const Symbol& symbol, MethodDeclaration* function) {
  functions_[symbol] = function;
}

MethodDeclaration* FunctionStorage::Get(const Symbol& symbol) {
  if (functions_.find(symbol) != functions_.end()) {
    return functions_.at(symbol);
  } else {
    throw std::runtime_error("Method not found");
  }
}
