#pragma once

#include <memory>
#include <stack>

#include "../objects/Method.h"

class FrameEmulator {
 public:
  explicit FrameEmulator(const std::shared_ptr<Method>& function);
  void SetParameters(const std::vector<Object*>& values);
  void SetFields(const std::vector<Object*>& values);

  size_t AllocVariable();

  void DeallocScope();
  void AllocScope();

  int Get(int index);

  void Set(int index, int value);

  void SetParentFrame(FrameEmulator* frame);

  int GetReturnValue() const;

  void SetParentReturnValue(int value);

  bool HasParent();

  int GetFieldSize() const;

 private:
  std::stack<int> offsets_;
  std::vector<Object*> parameters_;
  std::vector<Object*> variables_;

  int num_parameters = 0;
  int num_fields = 0;

  Object* return_value_{};

  void SetReturnValue(int value);

  FrameEmulator* parent_ = nullptr;
};
