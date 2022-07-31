#pragma once

#include <string>

namespace IRT {
enum class LogicOperatorType : char {
  LT,
  LE,
  GT,
  GE,
  EQ,
  NE
};

std::string ToString(LogicOperatorType type);

LogicOperatorType Invert(LogicOperatorType type);

LogicOperatorType Reverse(LogicOperatorType type);
}
