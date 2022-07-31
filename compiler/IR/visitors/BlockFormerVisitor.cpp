#include "BlockFormerVisitor.h"
#include "IRTNodes.h"

using namespace IRT;

BlockFormerVisitor::BlockFormerVisitor(std::string method_name)
    : method_name_(std::move(method_name)) {}

Statement* BlockFormerVisitor::GetTree() {
  return new SeqStatement(
      tos_value_.statement_,
      new SeqStatement(new JumpStatement(Label(method_name_ + "_done")),
                       new LabelStatement(Label(method_name_ + "_done"))));
}

void BlockFormerVisitor::Visit(ExpStatement* statement) {
  IRTStorage expr = Accept(statement->expression_);
  tos_value_.statement_ = new ExpStatement(expr.expression_);
}

void BlockFormerVisitor::Visit(ConstExpression* const_expression) {
  tos_value_.expression_ = new ConstExpression(const_expression->Value());
}

void BlockFormerVisitor::Visit(
    JumpConditionalStatement* jump_conditional_statement) {
  block_finished_ = true;

  IRTStorage lhs = Accept(jump_conditional_statement->left_operand_);
  IRTStorage rhs = Accept(jump_conditional_statement->right_operand_);

  tos_value_.statement_ = new JumpConditionalStatement(
      jump_conditional_statement->operator_type_, lhs.expression_,
      rhs.expression_, jump_conditional_statement->label_true_,
      jump_conditional_statement->label_false_);
}

void BlockFormerVisitor::Visit(MoveStatement* move_statement) {
  IRTStorage target = Accept(move_statement->target_);
  IRTStorage source = Accept(move_statement->source_);

  tos_value_.statement_ =
      new MoveStatement(target.expression_, source.expression_);
}

void BlockFormerVisitor::Visit(SeqStatement* seq_statement) {
  if (seq_statement->first_statement_->IsLabel()) {
    if (!block_finished_) {
      block_finished_ = true;

      auto label_statement =
          dynamic_cast<LabelStatement*>(seq_statement->first_statement_);

      IRTStorage first_statement = Accept(seq_statement->first_statement_);
      IRTStorage second_statement = Accept(seq_statement->second_statement_);

      tos_value_.statement_ =
          new SeqStatement(new JumpStatement(label_statement->label_),
                           new SeqStatement(first_statement.statement_,
                                            second_statement.statement_));
    } else {
      block_finished_ = false;

      IRTStorage first_statement = Accept(seq_statement->first_statement_);
      IRTStorage second_statement = Accept(seq_statement->second_statement_);

      tos_value_.statement_ = new SeqStatement(first_statement.statement_,
                                               second_statement.statement_);
    }
  } else {
    IRTStorage first_statement = Accept(seq_statement->first_statement_);
    IRTStorage second_statement = Accept(seq_statement->second_statement_);

    tos_value_.statement_ = new SeqStatement(first_statement.statement_,
                                             second_statement.statement_);
  }
}

void BlockFormerVisitor::Visit(LabelStatement* label_statement) {
  tos_value_.statement_ = new LabelStatement(label_statement->label_);
}

void BlockFormerVisitor::Visit(BinopExpression* binop_expression) {
  IRTStorage first = Accept(binop_expression->lhs_);
  IRTStorage second = Accept(binop_expression->rhs_);

  tos_value_.expression_ = new BinopExpression(
      binop_expression->type_, first.expression_, second.expression_);
}

void BlockFormerVisitor::Visit(TempExpression* temp_expression) {
  tos_value_.expression_ = new TempExpression(temp_expression->temporary_);
}

void BlockFormerVisitor::Visit(MemExpression* mem_expression) {
  IRTStorage expr = Accept(mem_expression->expression_);

  tos_value_.expression_ = new MemExpression(expr.expression_);
}

void BlockFormerVisitor::Visit(JumpStatement* jump_statement) {
  block_finished_ = true;
  tos_value_.statement_ = new JumpStatement(jump_statement->label_);
}

void BlockFormerVisitor::Visit(CallExpression* call_expression) {
  IRTStorage func = Accept(call_expression->function_name_);
  IRTStorage args = Accept(call_expression->args_);

  tos_value_.expression_ =
      new CallExpression(func.expression_, args.expression_list_);
}

void BlockFormerVisitor::Visit(ExpressionList* expression_list) {
  auto new_expression_list = new ExpressionList();

  for (Expression* expression : expression_list->expressions_) {
    new_expression_list->Add(Accept(expression).expression_);
  }

  tos_value_.expression_list_ = new_expression_list;
}

void BlockFormerVisitor::Visit(NameExpression* name_expression) {
  tos_value_.expression_ = new NameExpression(name_expression->label_);
}

void BlockFormerVisitor::Visit(EseqExpression* eseq_expression) {
  IRTStorage stmt = Accept(eseq_expression->statement_);
  IRTStorage expr = Accept(eseq_expression->expression_);

  tos_value_.expression_ =
      new EseqExpression(stmt.statement_, expr.expression_);
}
