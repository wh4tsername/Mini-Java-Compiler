#include "BlockBuilderVisitor.h"
#include "IRTNodes.h"

using namespace IRT;

BlockBuilderVisitor::BlockBuilderVisitor()
    : current_root_(nullptr), root_block_(nullptr) {}

void BlockBuilderVisitor::Visit(ExpStatement *stmt) {
  stmt->expression_->Accept(this);
}

void BlockBuilderVisitor::Visit(ConstExpression *const_expression) {}

void BlockBuilderVisitor::Visit(
    JumpConditionalStatement *jump_conditional_statement) {
  blocks_[current_label_.ToString()] = new ConditionalBlock(
      current_label_, current_root_, jump_conditional_statement->label_true_,
      jump_conditional_statement->label_false_);

  if (root_block_ == nullptr) {
    root_block_ = blocks_[current_label_.ToString()];
  }

  jump_conditional_statement->left_operand_->Accept(this);
  jump_conditional_statement->right_operand_->Accept(this);
}

void BlockBuilderVisitor::Visit(MoveStatement *move_statement) {
  move_statement->target_->Accept(this);
  move_statement->source_->Accept(this);
}

void BlockBuilderVisitor::Visit(SeqStatement *seq_statement) {
  if (seq_statement->first_statement_->IsLabel()) {
    current_label_ =
        dynamic_cast<LabelStatement *>(seq_statement->first_statement_)->label_;
    current_root_ = seq_statement->second_statement_;
  }

  seq_statement->first_statement_->Accept(this);
  seq_statement->second_statement_->Accept(this);
}

void BlockBuilderVisitor::Visit(LabelStatement *label_statement) {}

void BlockBuilderVisitor::Visit(BinopExpression *binop_statement) {
  binop_statement->lhs_->Accept(this);
  binop_statement->rhs_->Accept(this);
}

void BlockBuilderVisitor::Visit(TempExpression *temp_exression) {}

void BlockBuilderVisitor::Visit(MemExpression *mem_expression) {
  mem_expression->expression_->Accept(this);
}

void BlockBuilderVisitor::Visit(JumpStatement *jump_statement) {
  blocks_[current_label_.ToString()] =
      new SimpleBlock(current_label_, current_root_, jump_statement->label_);

  if (root_block_ == nullptr) {
    root_block_ = blocks_[current_label_.ToString()];
  }
}

void BlockBuilderVisitor::Visit(CallExpression *call_expression) {
  call_expression->function_name_->Accept(this);
  call_expression->args_->Accept(this);
}

void BlockBuilderVisitor::Visit(ExpressionList *expression_list) {
  for (auto &expression : expression_list->expressions_) {
    expression->Accept(this);
  }
}

void BlockBuilderVisitor::Visit(NameExpression *name_expression) {}

void BlockBuilderVisitor::Visit(EseqExpression *eseq_expression) {
  eseq_expression->statement_->Accept(this);
  eseq_expression->expression_->Accept(this);
}

BlockGraph BlockBuilderVisitor::BuildGraph() {
  for (auto& block_view : blocks_) {
    auto& block = block_view.second;

    if (block != nullptr) {
      if (block->IsSimple()) {
        auto simple_block = dynamic_cast<SimpleBlock *>(block);

        simple_block->next_block_ =
            blocks_[simple_block->GetNextBlockLabel().ToString()];
      } else {
        auto conditional_block = dynamic_cast<ConditionalBlock *>(block);

        conditional_block->true_block_ =
            blocks_[conditional_block->GetTrueBlockLabel().ToString()];
        conditional_block->false_block_ =
            blocks_[conditional_block->GetFalseBlockLabel().ToString()];
      }
    }
  }

  return BlockGraph(root_block_);
}
