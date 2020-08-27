#include "LogicOperatorType.h"

std::string IRT::ToString(IRT::LogicOperatorType type) {
  switch (type) {
    case LogicOperatorType::EQ:
      return "EQ";
    case LogicOperatorType::NE:
      return "NE";
    case LogicOperatorType::LT:
      return "LT";
    case LogicOperatorType::GT:
      return "GT";
    case LogicOperatorType::LE:
      return "LE";
    case LogicOperatorType::GE:
      return "GE";
  }
}

IRT::LogicOperatorType IRT::Invert(LogicOperatorType type) {
  switch (type) {
    case LogicOperatorType::EQ:
      return LogicOperatorType::NE;
    case LogicOperatorType::NE:
      return LogicOperatorType::EQ;
    case LogicOperatorType::LT:
      return LogicOperatorType::GE;
    case LogicOperatorType::GT:
      return LogicOperatorType::LE;
    case LogicOperatorType::LE:
      return LogicOperatorType::GT;
    case LogicOperatorType::GE:
      return LogicOperatorType::LT;
  }
}

IRT::LogicOperatorType IRT::Reverse(LogicOperatorType type) {
  switch (type) {
    case LogicOperatorType::EQ:
      return LogicOperatorType::EQ;
    case LogicOperatorType::NE:
      return LogicOperatorType::NE;
    case LogicOperatorType::LT:
      return LogicOperatorType::GT;
    case LogicOperatorType::GT:
      return LogicOperatorType::LT;
    case LogicOperatorType::LE:
      return LogicOperatorType::GE;
    case LogicOperatorType::GE:
      return LogicOperatorType::LE;
  }
}
