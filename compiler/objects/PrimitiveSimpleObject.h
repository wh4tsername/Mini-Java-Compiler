#pragma once

#include "PrimitiveObject.h"
#include "../function_processing/ClassStorage.h"
#include "../classes/Type.h"

class PrimitiveSimpleObject : public PrimitiveObject {
 public:
  explicit PrimitiveSimpleObject(Type* type);

  bool IsClass();
  bool IsArray() override;
  std::string GetTypename() override;
  size_t GetSize() override;

  Type* type_;
  bool is_class_;
};
