#pragma once

#include "PrimitiveSimpleObject.h"
#include "../classes/ArrayType.h"

class PrimitiveArrayObject : public PrimitiveObject {
 public:
  explicit PrimitiveArrayObject(PrimitiveSimpleObject* primitive_simple_object);
  explicit PrimitiveArrayObject(ArrayType* type);

  bool IsArray() override;
  std::string GetTypename() override;
  std::size_t GetSize() override;

  PrimitiveSimpleObject* simple_object_;
};
