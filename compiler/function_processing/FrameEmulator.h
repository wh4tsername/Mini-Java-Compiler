#pragma once

#include <memory>
#include <stack>

#include "../objects/Function.h"

class FrameEmulator {
 public:
  explicit FrameEmulator(std::shared_ptr<Function> function);
  void SetParameters(const std::vector<int>& values);

  size_t AllocVariable();

  void DeallocScope();
  void AllocScope();

  int Get(int index);

  void Set(int index, int value);

  void SetParentFrame(FrameEmulator* frame);

  int GetReturnValue() const;

  void SetParentReturnValue(int value);

  bool HasParent();

 private:
  std::stack<int> offsets_;
  std::vector<int> parameters_;
  std::vector<int> variables_;

  int return_value_ = 0;

  void SetReturnValue(int value);

  FrameEmulator* parent_ = nullptr;
};
