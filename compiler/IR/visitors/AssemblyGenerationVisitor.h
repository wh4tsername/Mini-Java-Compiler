#pragma once

#include <vector>

#include "../assembly/Instruction.h"
#include "../generators/Temporary.h"
#include "TemplateVisitor.h"

namespace IRT {

class AssemblyGenerationVisitor : public TemplateVisitor<Temporary> {
 public:
  explicit AssemblyGenerationVisitor(size_t num_args, size_t frame_size);

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

  void PrintAssembly(const std::string& filename);

 private:
  void FormMethodInstructionsSet();

  void ProcessCallExpression(CallExpression *call_expression, const Temporary& result_tmp);

  std::vector<Instruction> instructions_;

  size_t num_args_;
  size_t frame_size_;
  bool method_instr_set_formed_;
};

}  // namespace IRT
