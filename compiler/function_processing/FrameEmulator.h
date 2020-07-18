#pragma once

#include <memory>
#include <stack>

#include "../objects/Method.h"
#include "../objects/PrimitiveArrayObject.h"
#include "../objects/PrimitiveSimpleObject.h"
#include "../objects/values/Value.h"
#include "../objects/values/VariableValue.h"
#include "../objects/values/ArrayValue.h"

class FrameEmulator {
 public:
  explicit FrameEmulator(const std::shared_ptr<Method>& function);
  void SetParameters(const std::vector<Value*>& values);
  void SetFields(const std::vector<Value*>& values);

  size_t AllocVariable(PrimitiveObject* primitive_object);

  void DeallocScope();
  void AllocScope();

  Value* Get(int index);

  void Set(int index, Value* value);

  void SetParentFrame(FrameEmulator* frame);

  Value* GetReturnValue() const;

  void SetParentReturnValue(Value* value);

  bool HasParent();

  int GetFieldSize() const;

 private:
  std::stack<int> offsets_;
  std::vector<Value*> parameters_;
  std::vector<Value*> variables_;

  int num_parameters = 0;
  int num_fields = 0;

  Value* return_value_{};

  void SetReturnValue(Value* value);

  FrameEmulator* parent_ = nullptr;
};
