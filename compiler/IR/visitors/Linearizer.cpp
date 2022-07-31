#include "Linearizer.h"
#include "IRTNodes.h"

void IRT::Linearizer::Visit(IRT::ExpStatement *stmt) {
  IRTStorage elements = Accept(stmt->expression_);
  tos_value_.statement_ = new ExpStatement(elements.expression_);
}

void IRT::Linearizer::Visit(IRT::ConstExpression *const_expression) {
  tos_value_.expression_ = new ConstExpression(const_expression->Value());
}

void IRT::Linearizer::Visit(
    IRT::JumpConditionalStatement *jump_conditional_statement) {
  auto lhs = Accept(jump_conditional_statement->left_operand_).expression_;
  auto rhs = Accept(jump_conditional_statement->right_operand_).expression_;

  tos_value_.statement_ = new JumpConditionalStatement(
      jump_conditional_statement->operator_type_, lhs, rhs,
      jump_conditional_statement->label_true_,
      jump_conditional_statement->label_false_);
}

void IRT::Linearizer::Visit(IRT::MoveStatement *move_statement) {
  auto source = Accept(move_statement->source_).expression_;
  auto target = Accept(move_statement->target_).expression_;

  tos_value_.statement_ = new MoveStatement(source, target);
}

void IRT::Linearizer::Visit(IRT::SeqStatement *seq_statement) {
  auto first = Accept(seq_statement->first_statement_).statement_;
  auto second = Accept(seq_statement->second_statement_).statement_;
  if (first->IsSeq()) {
    auto seq = dynamic_cast<SeqStatement *>(first);
    tos_value_.statement_ =
        new SeqStatement(seq->first_statement_,
                         new SeqStatement(seq->second_statement_, second));
  } else {
    tos_value_.statement_ = new SeqStatement(first, second);
  }
}

void IRT::Linearizer::Visit(IRT::LabelStatement *label_statement) {
  tos_value_.statement_ = new LabelStatement(label_statement->label_);
}

void IRT::Linearizer::Visit(IRT::BinopExpression *binop_statement) {
  tos_value_.expression_ = new BinopExpression(
      binop_statement->type_, Accept(binop_statement->lhs_).expression_,
      Accept(binop_statement->rhs_).expression_);
}

void IRT::Linearizer::Visit(IRT::TempExpression *temp_exression) {
  tos_value_.expression_ = new TempExpression(temp_exression->temporary_);
}

void IRT::Linearizer::Visit(IRT::MemExpression *mem_expression) {
  tos_value_.expression_ =
      new MemExpression(Accept(mem_expression->expression_).expression_);
}

void IRT::Linearizer::Visit(IRT::JumpStatement *jump_statement) {
  tos_value_.statement_ = new JumpStatement(jump_statement->label_);
}

void IRT::Linearizer::Visit(IRT::CallExpression *call_expression) {
  auto func = Accept(call_expression->function_name_).expression_;
  auto args = Accept(call_expression->args_).expression_list_;

  tos_value_.expression_ = new CallExpression(func, args);
}

void IRT::Linearizer::Visit(IRT::ExpressionList *expression_list) {
  auto expression_list_ = new ExpressionList();

  for (auto expression : expression_list->expressions_) {
    expression_list_->Add(Accept(expression).expression_);
  }
  tos_value_.expression_list_ = expression_list_;
}

void IRT::Linearizer::Visit(IRT::NameExpression *name_expression) {
  tos_value_.expression_ = new NameExpression(name_expression->label_);
}

void IRT::Linearizer::Visit(IRT::EseqExpression *eseq_expression) {
  auto stmt = Accept(eseq_expression->statement_).statement_;
  auto expr = Accept(eseq_expression->expression_).expression_;

  tos_value_.expression_ = new EseqExpression(stmt, expr);
}

IRT::Statement *IRT::Linearizer::GetTree() { return tos_value_.statement_; }
