#pragma once

#include "../classes/statements/MethodDeclaration.h"
#include "../objects/Object.h"
#include "Symbol.h"

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

class ScopeLayer {
 public:
  explicit ScopeLayer(ScopeLayer* parent);
  ScopeLayer();
  ~ScopeLayer();
  void DeclareVariable(const Symbol& symbol);
  void DeclareFunction(const Symbol& symbol, MethodDeclaration* function);
  void Put(const Symbol& symbol, std::shared_ptr<Object> value);
  std::shared_ptr<Object> Get(const Symbol& symbol);
  bool Has(const Symbol& symbol);

  void AddChild(ScopeLayer* child);
  void AttachParent();

  ScopeLayer* GetChild(size_t index);
  ScopeLayer* GetParent() const;

  void PrintLayer(std::ostream& stream, int num_tabs) const;

  const std::unordered_map<Symbol, std::shared_ptr<Object>>& GetValues() const;
  const std::vector<Symbol>& GetFields() const;
  void SetFields(const std::vector<Symbol>& fields);

 private:
  std::unordered_map<Symbol, std::shared_ptr<Object>> values_;
  std::unordered_map<Symbol, size_t> offsets_;
  std::vector<Symbol> symbols_;
  std::vector<Symbol> fields_;
  std::string name_;
  ScopeLayer* parent_;
  std::vector<ScopeLayer*> children_;
};