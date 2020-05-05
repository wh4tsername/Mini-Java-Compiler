#pragma once

#include <unordered_map>

#include "../classes/statements/MethodDeclaration.h"
#include "../symbol_table/Symbol.h"

class FunctionStorage {
 public:
  static FunctionStorage& GetInstance();
  void Set(const Symbol& symbol, MethodDeclaration* function);
  MethodDeclaration* Get(const Symbol& symbol);

  FunctionStorage(const FunctionStorage& other) = delete;
  FunctionStorage& operator=(const FunctionStorage& other) = delete;

 private:
  FunctionStorage() = default;
  ~FunctionStorage() = default;

  std::unordered_map<Symbol, MethodDeclaration*> functions_;
};
