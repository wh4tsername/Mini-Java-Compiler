#pragma once

#include <string>

#include "IRTStorage.h"
#include "TemplateVisitor.h"

namespace IRT {

class BlockFormerVisitor : public TemplateVisitor<IRTStorage> {
 public:
  explicit BlockFormerVisitor(std::string method_name);

  Statement *GetTree();

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

 private:
  bool block_finished_ = true;

  std::string method_name_;
};

}  // namespace IRT
