#include "LogicalExpression.h"

LogicalExpression::LogicalExpression(std::string operation, Expression* lhs,
                                     Expression* rhs)
    : operation_(std::move(operation)), lhs_(lhs), rhs_(rhs) {}

int LogicalExpression::Count() {
  if (operation_ == "true") {
    return 1;
  }
  if (operation_ == "false") {
    return 0;
  }

  if (operation_ == "&&") {
    return static_cast<bool>(lhs_->Count()) && static_cast<bool>(rhs_->Count());
  }
  if (operation_ == "||") {
    return static_cast<bool>(lhs_->Count()) || static_cast<bool>(rhs_->Count());
  }
  if (operation_ == "!") {
    return !static_cast<bool>(lhs_->Count());
  }

  int lhs_value = lhs_->Count();
  int rhs_value = rhs_->Count();
  if (operation_ == "==") {
    return lhs_value == rhs_value;
  } else if (operation_ == "<") {
    return lhs_value < rhs_value;
  } else if (operation_ == ">") {
    return lhs_value > rhs_value;
  } else if (operation_ == "!=") {
    return lhs_value != rhs_value;
  } else if (operation_ == ">=") {
    return lhs_value >= rhs_value;
  } else if (operation_ == "<=") {
    return lhs_value <= rhs_value;
  }

  exit(RUNTIME_ERROR);
}

void LogicalExpression::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
