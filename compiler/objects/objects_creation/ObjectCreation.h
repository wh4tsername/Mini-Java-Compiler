#pragma once

#include "../../IR/generators/Temporary.h"
#include "../../IR/nodes/ExpressionList.h"
#include "../../IR/nodes/expressions/BinopExpression.h"
#include "../../IR/nodes/expressions/CallExpression.h"
#include "../../IR/nodes/expressions/ConstExpression.h"
#include "../../IR/nodes/expressions/EseqExpression.h"
#include "../../IR/nodes/expressions/MemExpression.h"
#include "../../IR/nodes/expressions/NameExpression.h"
#include "../../IR/nodes/expressions/TempExpression.h"
#include "../../IR/nodes/statements/MoveStatement.h"
#include "../../IR/nodes/statements/SeqStatement.h"
#include "../../IR/types/BinaryOperatorType.h"
#include "../PrimitiveSimpleObject.h"

IRT::Expression* CreateObject(PrimitiveSimpleObject* object) {
  auto* irt_expressions = new IRT::ExpressionList();
  irt_expressions->Add(new IRT::ConstExpression(object->GetSize()));

  IRT::Temporary tmp;
  return new IRT::EseqExpression(
      new IRT::MoveStatement(
          new IRT::TempExpression(tmp),
          new IRT::CallExpression(new IRT::NameExpression(IRT::Label("malloc")),
                                  irt_expressions)),
      new IRT::TempExpression(tmp));
}
