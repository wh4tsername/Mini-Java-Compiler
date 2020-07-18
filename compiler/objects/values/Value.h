#pragma once

#include <unordered_map>

#include "../Object.h"
#include "../../symbol_table/Symbol.h"
#include "../PrimitiveObject.h"

class Value {
 public:
  virtual void SetValue(int value) = 0;
  virtual void SetValue(Value* object) = 0;
  virtual int GetValue() = 0;
  virtual PrimitiveObject* GetType() = 0;
  virtual std::unordered_map<Symbol, Value*> GetFields() = 0;
};


