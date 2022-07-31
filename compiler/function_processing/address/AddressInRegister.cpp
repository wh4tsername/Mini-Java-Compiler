#include "AddressInRegister.h"

#include <utility>
#include "../../IR/nodes/expressions/TempExpression.h"

namespace IRT {
Expression* AddressInRegister::ToExpression() {
  return new TempExpression(temp_);
}

AddressInRegister::AddressInRegister(Temporary temp) : temp_(std::move(temp)) {}
}  // namespace IRT
