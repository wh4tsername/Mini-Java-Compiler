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

#define COMPILER_WORD_SIZE 4

// size of array is stored at one byte
IRT::Expression* CreateArray(IRT::Expression* array_size) {
  auto* irt_expressions = new IRT::ExpressionList();
  irt_expressions->Add(new IRT::BinopExpression(
      IRT::BinaryOperatorType::MUL, new IRT::ConstExpression(COMPILER_WORD_SIZE),
      new IRT::BinopExpression(IRT::BinaryOperatorType::PLUS, array_size,
                               new IRT::ConstExpression(1))));

  IRT::Temporary tmp;
  return new IRT::EseqExpression(
      new IRT::SeqStatement(
          new IRT::MoveStatement(
              new IRT::TempExpression(tmp),
              new IRT::CallExpression(
                  new IRT::NameExpression(IRT::Label("malloc")),
                  irt_expressions)),
          new IRT::MoveStatement(
              new IRT::MemExpression(new IRT::TempExpression(tmp)),
              array_size)),
      new IRT::TempExpression(tmp));
}
