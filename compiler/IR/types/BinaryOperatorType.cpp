#include "BinaryOperatorType.h"

std::string IRT::ToString(BinaryOperatorType type) {
  switch (type) {
    case BinaryOperatorType::PLUS:
      return "PLUS";
    case BinaryOperatorType::MINUS:
      return "MINUS";
    case BinaryOperatorType::MUL:
      return "MUL";
    case BinaryOperatorType::DIV:
      return "DIV";
    case BinaryOperatorType::AND:
      return "AND";
    case BinaryOperatorType::OR:
      return "OR";
    case BinaryOperatorType::MOD:
      return "MOD";
  }
}

bool IRT::IsCommutative(BinaryOperatorType type) {
  switch (type) {
    case BinaryOperatorType::PLUS:
      return true;
    case BinaryOperatorType::MINUS:
      return false;
    case BinaryOperatorType::MUL:
      return true;
    case BinaryOperatorType::DIV:
      return false;
    case BinaryOperatorType::AND:
      return true;
    case BinaryOperatorType::OR:
      return true;
    case BinaryOperatorType::MOD:
      return false;
  }
}
