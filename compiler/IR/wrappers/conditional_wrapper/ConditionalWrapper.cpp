#include "ConditionalWrapper.h"
#include "../../generators/Temporary.h"
#include "../../nodes/expressions/ConstExpression.h"
#include "../../nodes/expressions/EseqExpression.h"
#include "../../nodes/expressions/TempExpression.h"
#include "../../nodes/statements/LabelStatement.h"
#include "../../nodes/statements/MoveStatement.h"
#include "../../nodes/statements/SeqStatement.h"

using namespace IRT;

Expression* ConditionalWrapper::ToExpression() {
  auto* temp_expr = new TempExpression(Temporary());

  Label label_true;
  Label label_false;

  return new EseqExpression(
      new SeqStatement(
          new MoveStatement(temp_expr, new ConstExpression(1)),
          new SeqStatement(
              ToConditional(label_true, label_false),
              new SeqStatement(
                  new LabelStatement(label_false),
                  new SeqStatement(
                      new MoveStatement(temp_expr, new ConstExpression(0)),
                      new LabelStatement(label_true))))),
      temp_expr);
}

Statement* ConditionalWrapper::ToStatement() { return nullptr; }
