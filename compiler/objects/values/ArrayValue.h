#pragma once

#include <vector>

#include "../PrimitiveArrayObject.h"
#include "Value.h"

class ArrayValue : public Value {
 public:
  explicit ArrayValue(PrimitiveArrayObject* array_type);
  void SetValue(int value) override;
  void SetValue(Value* value) override;
  int GetValue() override;

  PrimitiveArrayObject* GetType() override;
  PrimitiveSimpleObject* GetElementType();
  void SetAtIndex(Value* value, size_t index);
  Value* AtIndex(size_t index);
  std::unordered_map<Symbol, Value*> GetFields() override;
  void Resize(size_t size);
  int GetSize();

 private:
  PrimitiveArrayObject* type_;
  PrimitiveSimpleObject* element_type_;
  std::vector<Value*> buffer_;
};
