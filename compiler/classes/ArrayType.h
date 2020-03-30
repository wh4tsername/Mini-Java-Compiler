#pragma once

#include "Type.h"

class ArrayType : public Type {
 public:
  explicit ArrayType(Type *type);

  void Accept(Visitor* visitor) override;
};
