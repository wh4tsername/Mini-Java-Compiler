#pragma once

#include <unordered_map>
#include <memory>
#include <utility>

#include "../classes/statements/ClassDeclaration.h"
#include "../objects/Method.h"
#include "../objects/PrimitiveObject.h"
#include "../symbol_table/Symbol.h"

class ClassStorage {
 public:
  static ClassStorage& GetInstance();
  ClassStorage(const ClassStorage& other) = delete;
  ClassStorage& operator=(const ClassStorage&) = delete;

  void SetMethod(
      const Symbol& symbol,
      std::unordered_map<Symbol, std::shared_ptr<Method>> methods);
  void SetField(
      const Symbol& symbol,
      std::unordered_map<Symbol, std::shared_ptr<PrimitiveObject>> fields);

  std::unordered_map<Symbol, std::shared_ptr<Method>> GetMethods(
      const Symbol& symbol) const;
  std::unordered_map<Symbol, std::shared_ptr<PrimitiveObject>> GetFields(
      const Symbol& symbol) const;

  std::vector<Symbol> GetMethodsNames(const Symbol& symbol);
  void SetClassMethodsNames(const Symbol& symbol,
                            std::vector<Symbol> class_methods_names);

  std::vector<Symbol> GetFieldsNames(const Symbol& symbol);
  void SetClassFieldsNames(const Symbol& symbol,
                           std::vector<Symbol> class_methods_names);

 private:
  ClassStorage() = default;
  ~ClassStorage() = default;

  std::unordered_map<Symbol, std::vector<Symbol>> class_methods_names_;
  std::unordered_map<Symbol, std::vector<Symbol>> class_fields_names_;
  std::unordered_map<Symbol,
                     std::unordered_map<Symbol, std::shared_ptr<Method>>>
      class_methods_;
  std::unordered_map<Symbol,
                     std::unordered_map<Symbol, std::shared_ptr<PrimitiveObject>>>
      class_fields_;
};
