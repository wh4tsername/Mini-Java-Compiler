#pragma once

#include "../../IR/generators/Temporary.h"
#include "Address.h"

namespace IRT {
class AddressInRegister : public Address {
 public:
  explicit AddressInRegister(Temporary  temp);
  Expression* ToExpression() override;

 private:
  Temporary temp_;
};
}
