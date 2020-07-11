#pragma once

#include "../../function_processing/ClassStorage.h"
#include "../PrimitiveArrayObject.h"
#include "../PrimitiveSimpleObject.h"
#include "ArrayValue.h"
#include "Value.h"

class VariableValue : public Value {
 public:
  explicit VariableValue(PrimitiveSimpleObject* type);
  VariableValue(PrimitiveSimpleObject* type, int value);
  void SetValue(int value) override;
  void SetValue(Value* object) override;
  int GetValue() override;

  PrimitiveSimpleObject* GetType() override;
  std::unordered_map<Symbol, Value*> GetFields() override;

 private:
  PrimitiveSimpleObject* type_;
  int value_ = 0;
  std::unordered_map<Symbol, Value*> fields_;
};
