#include "FunctionTable.h"

void FunctionTable::Put(const Symbol& symbol, int value) {
  if (values_.find(symbol) == values_.end()) {
    throw std::runtime_error(symbol.GetName() + ": variable not declared");
  }

  values_[symbol].pop();
  values_[symbol].push(value);
  symbols_.push(symbol);
}

int FunctionTable::Get(Symbol symbol) {
  if (values_.find(symbol) == values_.end()) {
    throw std::runtime_error(symbol.GetName() + ": variable not declared");
  }

  return values_[symbol].top();
}

void FunctionTable::CreateVariable(Symbol symbol) {
  if (values_.find(symbol) == values_.end()) {
    values_[symbol] = std::stack<int>();
  }

  values_[symbol].push(0);
}

void FunctionTable::BeginScope() {
  symbols_.push(Symbol("{"));
}

void FunctionTable::EndScope() {
  while (symbols_.top() != Symbol("{")) {
    Symbol symbol = symbols_.top();
    values_[symbol].pop();

    if (values_[symbol].empty()) {
      values_.erase(symbol);
    }
    symbols_.pop();
  }
  symbols_.pop();
}
