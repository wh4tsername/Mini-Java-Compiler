#pragma once

#include <stack>
#include <unordered_map>

#include "../symbol_table/Symbol.h"

class FunctionTable {
 public:
  void Put(Symbol symbol, int value);

  void CreateVariable(Symbol symbol);

  int Get(Symbol symbol);

  void BeginScope();
  void EndScope();

 private:
  std::unordered_map<Symbol, std::stack<int>> values_;
  std::stack<Symbol> symbols_;
};
