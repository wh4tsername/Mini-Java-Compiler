#pragma once

#include "Object.h"

class UninitObject : public Object {
 public:
  int ToInt() override;
};
