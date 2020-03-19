#include "ArithmeticalExpression.h"

ArithmeticalExpression::ArithmeticalExpression(std::string operation,
                                               Expression* lhs, Expression* rhs)
    : operation_(std::move(operation)), lhs_(lhs), rhs_(rhs) {}

int ArithmeticalExpression::Count() {
  int lhs_value = 0;
  int rhs_value = 0;
  lhs_value = lhs_->Count();
  if (rhs_) {
    rhs_value = rhs_->Count();
  }

  if (operation_ == "+") {
    return lhs_value + rhs_value;
  }
  if (operation_ == "-") {
    return lhs_value - rhs_value;
  }
  if (operation_ == "*") {
    return lhs_value * rhs_value;
  }
  if (operation_ == "/") {
    if (rhs_value == 0) {
      std::cerr << "Runtime error: division by zero" << std::endl;
      exit(RUNTIME_ERROR);
    }

    return lhs_value / rhs_value;
  }
  if (operation_ == "%") {
    if (rhs_value == 0) {
      std::cerr << "Runtime error: division by zero" << std::endl;
      exit(RUNTIME_ERROR);
    }

    return lhs_value % rhs_value;
  }
  if (operation_ == "@") {
    return -lhs_value;
  }

  exit(RUNTIME_ERROR);
}
