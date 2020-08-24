#include "LabelStatement.h"

#include <utility>

using namespace IRT;

LabelStatement::LabelStatement(IRT::Label label) : label_(std::move(label)) {}

bool LabelStatement::IsLabel() {
  return true;
}

void LabelStatement::Accept(Visitor* visitor) { visitor->Visit(this); }
