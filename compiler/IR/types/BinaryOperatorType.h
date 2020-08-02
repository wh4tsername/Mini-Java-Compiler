#pragma once

#include <string>

namespace IRT {
enum class BinaryOperatorType : char {
  PLUS,
  MINUS,
  MUL,
  DIV,
  MOD,
  AND,
  OR
};

std::string ToString(BinaryOperatorType type);

}
