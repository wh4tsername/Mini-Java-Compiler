#include <fstream>

#include "AssemblyGenerationVisitor.h"
#include "IRTNodes.h"

using namespace IRT;

AssemblyGenerationVisitor::AssemblyGenerationVisitor(size_t num_args,
                                                     size_t frame_size)
    : num_args_(num_args),
      frame_size_(frame_size),
      method_instr_set_formed_(false) {}

void AssemblyGenerationVisitor::PrintAssembly(const std::string &filename) {
  if (!method_instr_set_formed_) {
    FormMethodInstructionsSet();
  }

  std::ofstream stream(filename);
  for (const Instruction& instruction : instructions_) {
    stream << instruction << std::endl;
  }
  stream.close();
}

void AssemblyGenerationVisitor::ProcessCallExpression(
    CallExpression *call_expression, const Temporary &result_tmp) {
  auto method_name_expr =
      dynamic_cast<NameExpression *>(call_expression->function_name_);

  std::vector<Temporary> args;
  for (auto expr : call_expression->args_->expressions_) {
    args.emplace_back(Accept(expr));
  }

  if (method_name_expr->label_.ToString() == "assert") {
    Temporary arg = *args.begin();

    std::string cmd("cmp s0, #0");
    instructions_.emplace_back(Instruction(cmd, {arg}, {}));

    cmd = "swieq 0x11";
    instructions_.emplace_back(Instruction(cmd, {}, {}));
  } else if (method_name_expr->label_.ToString() == "print") {
    Temporary arg = *args.begin();

    std::string cmd("ldr t0, =printf_fmt");
    instructions_.emplace_back(Instruction(cmd, {}, {Temporary("r0")}));

    cmd = "mov t0, s0";
    instructions_.emplace_back(Instruction(cmd, {arg}, {Temporary("r1")}));

    cmd = "bl printf";
    instructions_.emplace_back(Instruction(cmd, {}, {}));
  } else {
    std::string cmd("mov t0, s0");
    for (size_t i = 0; i < std::min(args.size(), static_cast<size_t>(4)); ++i) {
      instructions_.emplace_back(
          Instruction(cmd, {args[i]}, {Temporary("r" + std::to_string(i))}));
    }

    cmd = "str s0, [sp, #";
    for (size_t i = 4; i < args.size(); ++i) {
      instructions_.emplace_back(
          Instruction(cmd + std::to_string(-4 * i - 8) + "]", {args[i]}, {}));
    }

    cmd = "bl " + method_name_expr->label_.ToString();
    instructions_.emplace_back(Instruction(cmd, {}, {}));

    cmd = "mov t0, s0";
    instructions_.emplace_back(
        Instruction(cmd, {Temporary("r0")}, {result_tmp}));
  }
}

void AssemblyGenerationVisitor::FormMethodInstructionsSet() {
  std::vector<Instruction> prologue;

  prologue.emplace_back(
      Instruction("str s0, [sp, #-4]!", {Temporary("fp")}, {}));

  prologue.emplace_back(Instruction("add t0, sp, #0", {}, {Temporary("fp")}));

  prologue.emplace_back(
      Instruction("sub sp, sp, #" + std::to_string(frame_size_), {}, {}));

  for (int i = 0; i < std::min(static_cast<int>(num_args_), 4); ++i) {
    prologue.emplace_back(
        Instruction("str s0, [s1, #" + std::to_string(-4 * i - 4) + "]",
                    {Temporary("r" + std::to_string(i)), Temporary("fp")}, {}));
  }

  prologue.emplace_back(Instruction("push {r4-r10, lr}", {}, {}));

  instructions_.insert(instructions_.begin() + 1, prologue.begin(), prologue.end());

  std::vector<Instruction> epilogue;

  epilogue.emplace_back(Instruction("pop {r4-r10, lr}", {}, {}));

  epilogue.emplace_back(Instruction("mov t0, s0", {Temporary("::return_value")},
                                    {Temporary("r0")}));

  epilogue.emplace_back(Instruction("add sp, s0, #0", {Temporary("fp")}, {}));

  epilogue.emplace_back(Instruction("ldr t0, [sp], #4", {}, {Temporary("fp")}));

  epilogue.emplace_back(Instruction("bx lr", {}, {}));

  instructions_.insert(instructions_.end(), epilogue.begin(), epilogue.end());

  method_instr_set_formed_ = true;
}

////////////////////////////////////////////////////////////////////////////////

void AssemblyGenerationVisitor::Visit(ExpStatement *stmt) {
  stmt->expression_->Accept(this);
}

void AssemblyGenerationVisitor::Visit(ConstExpression *const_expression) {
  Temporary result_temp;

  std::string cmd("mov t0, #" + std::to_string(const_expression->Value()));

  instructions_.emplace_back(Instruction(cmd, {}, {result_temp}));

  tos_value_ = result_temp;
}

void AssemblyGenerationVisitor::Visit(
    JumpConditionalStatement *jump_conditional_statement) {
  LogicOperatorType op = jump_conditional_statement->operator_type_;

  if (jump_conditional_statement->right_operand_->IsCONST()) {
    auto lhs = Accept(jump_conditional_statement->left_operand_);
    auto rhs = dynamic_cast<ConstExpression *>(
        jump_conditional_statement->right_operand_);

    std::string cmd("cmp s0, #" + std::to_string(rhs->Value()));

    instructions_.emplace_back(Instruction(cmd, {lhs}, {}));
  } else if (jump_conditional_statement->left_operand_->IsCONST()) {
    auto lhs = dynamic_cast<ConstExpression *>(
        jump_conditional_statement->left_operand_);
    auto rhs = Accept(jump_conditional_statement->right_operand_);

    op = Reverse(op);

    std::string cmd("cmp s0, #" + std::to_string(lhs->Value()));

    instructions_.emplace_back(Instruction(cmd, {rhs}, {}));
  } else {
    auto lhs = Accept(jump_conditional_statement->left_operand_);
    auto rhs = Accept(jump_conditional_statement->right_operand_);

    std::string cmd("cmp s0, s1");

    instructions_.emplace_back(Instruction(cmd, {lhs, rhs}, {}));
  }

  std::string cmd;
  switch (op) {
    case LogicOperatorType::LT:
      cmd = "blt";
      break;
    case LogicOperatorType::LE:
      cmd = "ble";
      break;
    case LogicOperatorType::GT:
      cmd = "bgt";
      break;
    case LogicOperatorType::GE:
      cmd = "bge";
      break;
    case LogicOperatorType::EQ:
      cmd = "beq";
      break;
    case LogicOperatorType::NE:
      cmd = "bne";
      break;
  }

  cmd += " " + jump_conditional_statement->label_true_.ToString();
  instructions_.emplace_back(Instruction(cmd, {}, {}));

  cmd = "b " + jump_conditional_statement->label_false_.ToString();
  instructions_.emplace_back(Instruction(cmd, {}, {}));
}

void AssemblyGenerationVisitor::Visit(MoveStatement *move_statement) {
  Expression *target = move_statement->target_;
  Expression *source = move_statement->source_;

  if (target->IsMEM()) {
    auto mem_target = dynamic_cast<MemExpression *>(target);
    auto temp_source = Accept(move_statement->source_);

    if (source->IsMEM()) {
      auto source_node =
          new MoveStatement(target, new TempExpression(temp_source));
      source_node->Accept(this);
      // TODO
    } else if (mem_target->expression_->IsBINOP()) {
      auto binop = dynamic_cast<BinopExpression *>(mem_target->expression_);

      if (binop->type_ == BinaryOperatorType::PLUS) {
        if (binop->lhs_->IsCONST()) {
          auto lhs = dynamic_cast<ConstExpression *>(binop->lhs_);
          auto rhs = Accept(binop->rhs_);

          instructions_.emplace_back(
              Instruction("str s0, [s1, #" + std::to_string(lhs->Value()) + "]",
                          {temp_source, rhs}, {}));
        } else if (binop->rhs_->IsCONST()) {
          auto lhs = Accept(binop->lhs_);
          auto rhs = dynamic_cast<ConstExpression *>(binop->rhs_);

          instructions_.emplace_back(
              Instruction("str s0, [s1, #" + std::to_string(rhs->Value()) + "]",
                          {temp_source, lhs}, {}));
        } else {
          auto lhs = Accept(binop->lhs_);
          auto rhs = Accept(binop->rhs_);

          instructions_.emplace_back(
              Instruction("str s0, [s1, s2]", {temp_source, rhs, lhs}, {}));
        }
      } else {
        Temporary temp_binop = Accept(mem_target->expression_);

        instructions_.emplace_back(
            Instruction("str s0, [s1]", {temp_source, temp_binop}, {}));
      }
    } else {
      Temporary temp_target = Accept(mem_target->expression_);

      instructions_.emplace_back(
          Instruction("str s0, [s1]", {temp_source, temp_target}, {}));
    }
  } else if (source->IsMEM()) {
    auto temp_target = Accept(target);
    auto mem_source = dynamic_cast<MemExpression *>(source);

    if (mem_source->expression_->IsBINOP()) {
      auto binop = dynamic_cast<BinopExpression *>(mem_source->expression_);

      if (binop->type_ == BinaryOperatorType::PLUS) {
        if (binop->lhs_->IsCONST()) {
          auto lhs = dynamic_cast<ConstExpression *>(binop->lhs_);
          auto rhs = Accept(binop->rhs_);

          instructions_.emplace_back(
              Instruction("ldr t0, [s0, #" + std::to_string(lhs->Value()) + "]",
                          {rhs}, {temp_target}));
        } else if (binop->rhs_->IsCONST()) {
          auto lhs = Accept(binop->lhs_);
          auto rhs = dynamic_cast<ConstExpression *>(binop->rhs_);

          instructions_.emplace_back(
              Instruction("ldr t0, [s0, #" + std::to_string(rhs->Value()) + "]",
                          {lhs}, {temp_target}));
        } else {
          auto lhs = Accept(binop->lhs_);
          auto rhs = Accept(binop->rhs_);

          instructions_.emplace_back(
              Instruction("ldr t0, [s0, s1]", {lhs, rhs}, {temp_target}));
        }
      } else {
        auto temp_binop = Accept(mem_source->expression_);

        instructions_.emplace_back(
            Instruction("ldr t0, [s0]", {temp_binop}, {temp_target}));
      }
    } else {
      auto temp_source = Accept(mem_source->expression_);

      instructions_.emplace_back(
          Instruction("ldr t0, [s0]", {temp_source}, {temp_target}));
    }
  } else if (source->IsCONST()) {
    auto temp_target = Accept(target);
    auto const_source = dynamic_cast<ConstExpression *>(source);

    instructions_.emplace_back(
        Instruction("mov t0, #" + std::to_string(const_source->Value()), {},
                    {temp_target}));
  } else if (target->IsTEMP() && source->IsCALL()) {
    auto temp_target = dynamic_cast<TempExpression *>(target);
    auto call_source = dynamic_cast<CallExpression *>(source);

    ProcessCallExpression(call_source, temp_target->temporary_);
  } else {
    auto temp_target = Accept(target);
    auto temp_source = Accept(source);

    instructions_.emplace_back(
        Instruction("mov t0, s0", {temp_source}, {temp_target}));
  }
}

void AssemblyGenerationVisitor::Visit(SeqStatement *seq_statement) {
  seq_statement->first_statement_->Accept(this);
  seq_statement->second_statement_->Accept(this);
}

void AssemblyGenerationVisitor::Visit(LabelStatement *label_statement) {
  std::string cmd(label_statement->label_.ToString() + ":");
  instructions_.emplace_back(Instruction(cmd, {}, {}));
}

void AssemblyGenerationVisitor::Visit(BinopExpression *binop_statement) {
  Temporary result;

  if (binop_statement->lhs_->IsCONST() && binop_statement->rhs_->IsCONST()) {
    auto lhs = dynamic_cast<ConstExpression *>(binop_statement->lhs_);
    auto rhs = dynamic_cast<ConstExpression *>(binop_statement->rhs_);

    std::string cmd("mov t0, #(");
    switch (binop_statement->type_) {
      case BinaryOperatorType::PLUS:
        instructions_.emplace_back(
            Instruction(cmd + std::to_string(lhs->Value()) + "+" +
                            std::to_string(rhs->Value()) + ")",
                        {}, {result}));
        break;
      case BinaryOperatorType::MINUS:
        instructions_.emplace_back(
            Instruction(cmd + std::to_string(lhs->Value()) + "-" +
                            std::to_string(rhs->Value()) + ")",
                        {}, {result}));
        break;
      case BinaryOperatorType::MUL:
        instructions_.emplace_back(
            Instruction(cmd + std::to_string(lhs->Value()) + "*" +
                            std::to_string(rhs->Value()) + ")",
                        {}, {result}));
        break;
      case BinaryOperatorType::DIV:
        instructions_.emplace_back(
            Instruction(cmd + std::to_string(lhs->Value()) + "/" +
                            std::to_string(rhs->Value()) + ")",
                        {}, {result}));
        break;
      case BinaryOperatorType::MOD:
        instructions_.emplace_back(
            Instruction(cmd + std::to_string(lhs->Value()) + " mod " +
                            std::to_string(rhs->Value()) + ")",
                        {}, {result}));
        break;
      case BinaryOperatorType::AND:
        instructions_.emplace_back(
            Instruction(cmd + std::to_string(lhs->Value()) + " and " +
                            std::to_string(rhs->Value()) + ")",
                        {}, {result}));
        break;
      case BinaryOperatorType::OR:
        instructions_.emplace_back(
            Instruction(cmd + std::to_string(lhs->Value()) + " or " +
                            std::to_string(rhs->Value()) + ")",
                        {}, {result}));
        break;
    }
  } else if (binop_statement->rhs_->IsCONST()) {
    auto lhs = Accept(binop_statement->lhs_);
    auto rhs = dynamic_cast<ConstExpression *>(binop_statement->rhs_);

    switch (binop_statement->type_) {
      case BinaryOperatorType::PLUS:
        instructions_.emplace_back(Instruction(
            "add t0, s0, #" + std::to_string(rhs->Value()), {lhs}, {result}));
        break;
      case BinaryOperatorType::MINUS:
        instructions_.emplace_back(Instruction(
            "sub t0, s0, #" + std::to_string(rhs->Value()), {lhs}, {result}));
        break;
      case BinaryOperatorType::MUL:
        if (result == lhs) {
          instructions_.emplace_back(Instruction(
              "mul t0, #" + std::to_string(rhs->Value()), {lhs}, {result}));
        } else {
          Temporary temp;
          instructions_.emplace_back(Instruction(
              "mov t0, #" + std::to_string(rhs->Value()), {}, {temp}));
          instructions_.emplace_back(
              Instruction("mul t0, s0, s1", {lhs, temp}, {result}));
        }
        break;
      case BinaryOperatorType::DIV:
        instructions_.emplace_back(Instruction(
            "sdiv t0, s0, #" + std::to_string(rhs->Value()), {lhs}, {result}));
        break;
      case BinaryOperatorType::MOD: {
        Temporary temp;
        instructions_.emplace_back(Instruction(
            "sdiv t0, s0, #" + std::to_string(rhs->Value()), {lhs}, {temp}));
        instructions_.emplace_back(Instruction(
            "mul t0, #" + std::to_string(rhs->Value()), {}, {temp}));
        instructions_.emplace_back(
            Instruction("sub t0, s0, s1", {lhs, temp}, {result}));
      } break;
      case BinaryOperatorType::AND:
        instructions_.emplace_back(Instruction(
            "and t0, s0, #" + std::to_string(rhs->Value()), {lhs}, {result}));
        break;
      case BinaryOperatorType::OR:
        instructions_.emplace_back(Instruction(
            "orr t0, s0, #" + std::to_string(rhs->Value()), {lhs}, {result}));
        break;
    }
  } else if (binop_statement->lhs_->IsCONST() &&
             IsCommutative(binop_statement->type_)) {
    auto lhs = dynamic_cast<ConstExpression *>(binop_statement->lhs_);
    auto rhs = Accept(binop_statement->rhs_);

    switch (binop_statement->type_) {
      case BinaryOperatorType::PLUS:
        instructions_.emplace_back(Instruction(
            "add t0, s0, #" + std::to_string(lhs->Value()), {rhs}, {result}));
        break;
      case BinaryOperatorType::MUL:
        if (result == rhs) {
          instructions_.emplace_back(Instruction(
              "mul t0, #" + std::to_string(lhs->Value()), {rhs}, {result}));
        } else {
          Temporary temp;
          instructions_.emplace_back(Instruction(
              "mov t0, #" + std::to_string(lhs->Value()), {}, {temp}));
          instructions_.emplace_back(
              Instruction("mul t0, s0, s1", {rhs, temp}, {result}));
        }
        break;
      case BinaryOperatorType::AND:
        instructions_.emplace_back(Instruction(
            "and t0, s0, #" + std::to_string(lhs->Value()), {rhs}, {result}));
        break;
      case BinaryOperatorType::OR:
        instructions_.emplace_back(Instruction(
            "orr t0, s0, #" + std::to_string(lhs->Value()), {rhs}, {result}));
        break;
      default:
        throw std::runtime_error(
            "BinaryOperatorType: " + ToString(binop_statement->type_) +
            " doesn't commute!");
    }
  } else {
    Temporary lhs = Accept(binop_statement->lhs_);
    Temporary rhs = Accept(binop_statement->rhs_);

    switch (binop_statement->type_) {
      case BinaryOperatorType::PLUS:
        instructions_.emplace_back(
            Instruction("add t0, s0, s1", {lhs, rhs}, {result}));
        break;
      case BinaryOperatorType::MINUS:
        instructions_.emplace_back(
            Instruction("sub t0, s0, s1", {lhs, rhs}, {result}));
        break;
      case BinaryOperatorType::MUL:
        instructions_.emplace_back(
            Instruction("mul t0, s0, s1", {lhs, rhs}, {result}));
        break;
      case BinaryOperatorType::DIV:
        instructions_.emplace_back(
            Instruction("sdiv t0, s0, s1", {lhs, rhs}, {result}));
        break;
      case BinaryOperatorType::MOD: {
        Temporary temp;

        instructions_.emplace_back(
            Instruction("sdiv t0, s0, s1", {lhs, rhs}, {result}));
        instructions_.emplace_back(Instruction("mul t0, s0", {rhs}, {temp}));
        instructions_.emplace_back(
            Instruction("sub t0, s0, s1", {lhs, temp}, {result}));
      } break;
      case BinaryOperatorType::AND:
        instructions_.emplace_back(
            Instruction("and t0, s0, s1", {lhs, rhs}, {result}));
        break;
      case BinaryOperatorType::OR:
        instructions_.emplace_back(
            Instruction("orr t0, s0, s1", {lhs, rhs}, {result}));
        break;
    }
  }

  tos_value_ = result;
}

void AssemblyGenerationVisitor::Visit(TempExpression *temp_exression) {
  tos_value_ = temp_exression->temporary_;
}

void AssemblyGenerationVisitor::Visit(MemExpression *mem_expression) {
  Temporary result;
  if (mem_expression->expression_->IsBINOP()) {
    auto binop = dynamic_cast<BinopExpression *>(mem_expression->expression_);

    if (binop->type_ == BinaryOperatorType::PLUS) {
      if (binop->lhs_->IsCONST()) {
        auto lhs = dynamic_cast<ConstExpression *>(binop->lhs_);
        auto rhs = Accept(binop->rhs_);

        instructions_.emplace_back(
            Instruction("ldr t0, [s0, #" + std::to_string(lhs->Value()) + "]",
                        {rhs}, {result}));
      } else if (binop->rhs_->IsCONST()) {
        auto lhs = Accept(binop->lhs_);
        auto rhs = dynamic_cast<ConstExpression *>(binop->rhs_);

        instructions_.emplace_back(
            Instruction("ldr t0, [s0, #" + std::to_string(rhs->Value()) + "]",
                        {lhs}, {result}));
      } else {
        auto lhs = Accept(binop->lhs_);
        auto rhs = Accept(binop->rhs_);

        instructions_.emplace_back(
            Instruction("ldr t0, [s0, s1]", {lhs, rhs}, {result}));
      }
    } else {
      Temporary binop_result = Accept(mem_expression->expression_);

      instructions_.emplace_back(
          Instruction("ldr t0, [s0]", {binop_result}, {result}));
    }
  } else {
    Temporary expr_result = Accept(mem_expression->expression_);

    instructions_.emplace_back(
        Instruction("ldr t0, [s0]", {expr_result}, {result}));
  }

  tos_value_ = result;
}

void AssemblyGenerationVisitor::Visit(JumpStatement *jump_statement) {
  std::string cmd("b " + jump_statement->label_.ToString());
  instructions_.emplace_back(Instruction(cmd, {}, {}));
}

void AssemblyGenerationVisitor::Visit(CallExpression *call_expression) {
  Temporary returned("r0");
  ProcessCallExpression(call_expression, returned);
  tos_value_ = returned;
}

void AssemblyGenerationVisitor::Visit(ExpressionList *expression_list) {}

void AssemblyGenerationVisitor::Visit(NameExpression *name_expression) {}

void AssemblyGenerationVisitor::Visit(EseqExpression *eseq_expression) {
  eseq_expression->statement_->Accept(this);
  if (eseq_expression->expression_->IsTEMP()) {
    auto temp = dynamic_cast<TempExpression *>(eseq_expression->expression_);
    tos_value_ = temp->temporary_;
  } else {
    tos_value_ = Accept(eseq_expression->expression_);
  }
}
