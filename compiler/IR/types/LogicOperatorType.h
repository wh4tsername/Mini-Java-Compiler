#pragma once

#include <string>

namespace IRT {
enum class LogicOperatorType : char {
  LT,
  GT,
  EQ,
  NE
};

std::string ToString(LogicOperatorType type);
}
