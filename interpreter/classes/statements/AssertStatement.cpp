#include "AssertStatement.h"

AssertStatement::AssertStatement(Expression *expression)
    : expression_(expression) {}

void AssertStatement::Run() { assert(expression_->Count()); }
