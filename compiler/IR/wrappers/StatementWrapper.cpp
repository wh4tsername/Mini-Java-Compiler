#include <cassert>

#include "StatementWrapper.h"

using namespace IRT;

StatementWrapper::StatementWrapper(Statement* statement)
    : statement_(statement) {}

Expression* StatementWrapper::ToExpression() { assert(false); }

Statement* StatementWrapper::ToStatement() { return statement_; }

Statement* StatementWrapper::ToConditional(Label true_label,
                                           Label false_label) {
  assert(false);
}
