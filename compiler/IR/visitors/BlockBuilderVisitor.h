#pragma once

#include <map>

#include "../blocks/BlockGraph.h"
#include "IRTStorage.h"
#include "Visitor.h"

namespace IRT {

class BlockBuilderVisitor : public Visitor {
 public:
  BlockBuilderVisitor();

  void Visit(ExpStatement *stmt) override;
  void Visit(ConstExpression *const_expression) override;
  void Visit(JumpConditionalStatement *jump_conditional_statement) override;
  void Visit(MoveStatement *move_statement) override;
  void Visit(SeqStatement *seq_statement) override;
  void Visit(LabelStatement *label_statement) override;
  void Visit(BinopExpression *binop_statement) override;
  void Visit(TempExpression *temp_exression) override;
  void Visit(MemExpression *mem_expression) override;
  void Visit(JumpStatement *jump_statement) override;
  void Visit(CallExpression *call_expression) override;
  void Visit(ExpressionList *expression_list) override;
  void Visit(NameExpression *name_expression) override;
  void Visit(EseqExpression *eseq_expression) override;

  BlockGraph BuildGraph();

 private:
  Label current_label_;
  Statement *current_root_;
  Block *root_block_;

  std::map<std::string, Block *> blocks_;
};

}  // namespace IRT
