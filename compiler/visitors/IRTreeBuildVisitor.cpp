#include "IRTreeBuildVisitor.h"

#include "../objects/objects_creation/ArrayCreation.h"
#include "../objects/objects_creation/ObjectCreation.h"

#include "../function_processing/ClassStorage.h"

#include "../IR/nodes/statements/JumpStatement.h"
#include "../IR/nodes/statements/LabelStatement.h"

#include "../IR/wrappers/ExpressionWrapper.h"
#include "../IR/wrappers/StatementWrapper.h"
#include "../IR/wrappers/conditional_wrapper/AndConditionalWrapper.h"
#include "../IR/wrappers/conditional_wrapper/NegativeConditionalWrapper.h"
#include "../IR/wrappers/conditional_wrapper/OrConditionalWrapper.h"
#include "../IR/wrappers/conditional_wrapper/RelativeConditionalWrapper.h"

IRTreeBuildVisitor::IRTreeBuildVisitor(NewScopeLayerTree* tree) : tree_(tree) {
  tree_->root_->PrepareTraversing();
  current_layer_ = tree_->root_;
  current_frame_ = nullptr;
}

void IRTreeBuildVisitor::TraverseToChildByIndex() {
  if (current_layer_->traverse_index >= current_layer_->children_.size()) {
    throw std::runtime_error("Error while traversing...");
  }

  ++current_layer_->traverse_index;
  current_layer_ =
      current_layer_->children_[current_layer_->traverse_index - 1];
}

IrtMapping IRTreeBuildVisitor::GetTrees() { return method_trees_; }

NewScopeLayer* IRTreeBuildVisitor::GetCurrentLayer() const {
  return current_layer_;
}

std::string IRTreeBuildVisitor::GetCurrentClassName() const {
  return current_layer_->class_symbol_.GetName();
}

std::string IRTreeBuildVisitor::TypeResolving(const Symbol& symbol) const {
  NewScopeLayer* local_current = current_layer_;

  while (local_current->user_type_system_.find(symbol) ==
         local_current->user_type_system_.end()) {
    local_current = local_current->parent_;
  }

  return local_current->user_type_system_[symbol];
}

////////////////////////////////////////////////////////////////////////////////

void IRTreeBuildVisitor::Visit(AssertStatement* statement) {
  auto* irt_expr = new IRT::ExpressionList();
  irt_expr->Add(Accept(statement->expression_)->ToExpression());

  tos_value_ = new IRT::ExpressionWrapper(new IRT::CallExpression(
      new IRT::NameExpression(IRT::Label("assert")), irt_expr));
}

void IRTreeBuildVisitor::Visit(AssignmentStatement* statement) {
  auto var_expression = Accept(statement->lvalue_)->ToExpression();
  auto rvalue = Accept(statement->expression_);

  tos_value_ = new IRT::StatementWrapper(
      new IRT::MoveStatement(var_expression, rvalue->ToExpression()));
}

void IRTreeBuildVisitor::Visit(IfStatement* statement) {
  if (statement->else_statement_ == nullptr) {
    auto if_expression = Accept(statement->expression_);

    current_layer_ = current_layer_->children_[offsets_.top()];
    offsets_.push(0);
    current_frame_->SetupScope();
    auto true_stmt = Accept(statement->if_statement_);
    offsets_.pop();
    size_t index = offsets_.top();
    offsets_.pop();
    offsets_.push(index + 1);
    current_layer_ = current_layer_->parent_;
    current_frame_->TearDownScope();

    IRT::Label label_true;
    IRT::Label label_join;

    IRT::Statement* suffix = new IRT::LabelStatement(label_join);

    IRT::Label* result_true = &label_join;
    IRT::Label* result_false = &label_join;

    if (true_stmt) {
      result_true = &label_true;
      suffix = new IRT::SeqStatement(
          new IRT::LabelStatement(label_true),
          new IRT::SeqStatement(
              true_stmt->ToStatement(),
              new IRT::SeqStatement(new IRT::JumpStatement(label_join),
                                    suffix)));
    }

    tos_value_ = new IRT::StatementWrapper(new IRT::SeqStatement(
        if_expression->ToConditional(*result_true, *result_false), suffix));
  } else {
    auto if_expression = Accept(statement->expression_);

    current_layer_ = current_layer_->children_[offsets_.top()];
    offsets_.push(0);
    current_frame_->SetupScope();
    auto true_stmt = Accept(statement->if_statement_);
    offsets_.pop();
    size_t index = offsets_.top();
    offsets_.pop();
    offsets_.push(index + 1);
    current_layer_ = current_layer_->parent_;
    current_frame_->TearDownScope();

    current_layer_ = current_layer_->children_[offsets_.top()];
    offsets_.push(0);
    current_frame_->SetupScope();
    auto false_stmt = Accept(statement->else_statement_);
    offsets_.pop();
    index = offsets_.top();
    offsets_.pop();
    offsets_.push(index + 1);
    current_layer_ = current_layer_->parent_;
    current_frame_->TearDownScope();

    IRT::Label label_true;
    IRT::Label label_false;
    IRT::Label label_join;

    IRT::Statement* suffix = new IRT::LabelStatement(label_join);

    IRT::Label* result_true = &label_join;
    IRT::Label* result_false = &label_join;

    if (false_stmt) {
      result_false = &label_false;
      suffix = new IRT::SeqStatement(
          new IRT::LabelStatement(label_false),
          new IRT::SeqStatement(false_stmt->ToStatement(), suffix));

      if (true_stmt) {
        suffix =
            new IRT::SeqStatement(new IRT::JumpStatement(label_join), suffix);
      }
    }

    if (true_stmt) {
      result_true = &label_true;
      suffix = new IRT::SeqStatement(
          new IRT::LabelStatement(label_true),
          new IRT::SeqStatement(true_stmt->ToStatement(), suffix));
    }

    tos_value_ = new IRT::StatementWrapper(new IRT::SeqStatement(
        if_expression->ToConditional(*result_true, *result_false), suffix));
  }
}

void IRTreeBuildVisitor::Visit(ReturnStatement* statement) {
  auto return_expr = Accept(statement->expression_);

  tos_value_ = new IRT::StatementWrapper(new IRT::MoveStatement(
      current_frame_->GetReturnValueAddress(), return_expr->ToExpression()));
}

void IRTreeBuildVisitor::Visit(
    ScopeListOfStatements* scope_list_of_statements) {
  scope_list_of_statements->list_of_statements_->Accept(this);
}

void IRTreeBuildVisitor::Visit(PrintStatement* statement) {
  auto* irt_expressions = new IRT::ExpressionList();
  irt_expressions->Add(Accept(statement->expression_)->ToExpression());

  tos_value_ = new IRT::ExpressionWrapper(new IRT::CallExpression(
      new IRT::NameExpression(IRT::Label("print")), irt_expressions));
}

void IRTreeBuildVisitor::Visit(ListOfStatements* list_of_statements) {
  auto& statements = list_of_statements->list_of_statements_;
  if (statements.empty()) {
    tos_value_ = nullptr;
  } else if (statements.size() == 1) {
    tos_value_ = Accept(statements[0]);
  } else {
    std::vector<IRT::Statement*> ir_statements;
    for (auto&& statement : statements) {
      auto ir_statement = Accept(statement);
      if (ir_statement) {
        ir_statements.emplace_back(ir_statement->ToStatement());
      }
    }

    IRT::Statement* suffix = ir_statements.back();
    for (int i = static_cast<int>(statements.size()) - 2; i >= 0; --i) {
      suffix = new IRT::SeqStatement(ir_statements[i], suffix);
    }

    tos_value_ = new IRT::StatementWrapper(suffix);
  }
}

void IRTreeBuildVisitor::Visit(WhileStatement* statement) {
  auto if_expression = Accept(statement->expression_);

  current_layer_ = current_layer_->children_[offsets_.top()];
  offsets_.push(0);
  current_frame_->SetupScope();
  auto while_stmt = Accept(statement->statement_);
  offsets_.pop();
  size_t index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);
  current_layer_ = current_layer_->parent_;
  current_frame_->TearDownScope();

  IRT::Label label_cond;
  IRT::Label label_true;
  IRT::Label label_join;

  IRT::Statement* suffix = new IRT::LabelStatement(label_join);

  IRT::Label* result_true = &label_join;

  if (while_stmt) {
    result_true = &label_true;
    suffix = new IRT::SeqStatement(
        new IRT::LabelStatement(label_true),
        new IRT::SeqStatement(
            while_stmt->ToStatement(),
            new IRT::SeqStatement(new IRT::JumpStatement(label_cond), suffix)));
  }

  tos_value_ = new IRT::StatementWrapper(new IRT::SeqStatement(
      new IRT::LabelStatement(label_cond),
      new IRT::SeqStatement(
          if_expression->ToConditional(*result_true, label_join), suffix)));
}

void IRTreeBuildVisitor::Visit(ArrayAccessExpression* expression) {
  auto address = current_frame_->GetAddress(expression->array_indent_);
  auto array_ident_expr = (new IRT::ExpressionWrapper(address))->ToExpression();

  auto index = Accept(expression->index_expression_)->ToExpression();

  tos_value_ = new IRT::ExpressionWrapper(
      new IRT::MemExpression(new IRT::BinopExpression(
          IRT::BinaryOperatorType::PLUS, array_ident_expr,
          new IRT::BinopExpression(
              IRT::BinaryOperatorType::MUL,
              new IRT::BinopExpression(IRT::BinaryOperatorType::PLUS, index,
                                       new IRT::ConstExpression(1)),
              new IRT::ConstExpression(COMPILER_WORD_SIZE)))));
}

void IRTreeBuildVisitor::Visit(NewArrayExpression* expression) {
  auto size_expr = Accept(expression->length_)->ToExpression();
  auto array = CreateArray(size_expr);

  tos_value_ = new IRT::ExpressionWrapper(array);
}

void IRTreeBuildVisitor::Visit(LengthExpression* expression) {
  auto address = current_frame_->GetAddress(expression->variable_name_);
  auto array_ident_expr = (new IRT::ExpressionWrapper(address))->ToExpression();

  tos_value_ =
      new IRT::ExpressionWrapper(new IRT::MemExpression(array_ident_expr));
}

void IRTreeBuildVisitor::Visit(LogicalExpression* expression) {
  const std::string& op = expression->operation_;
  if (expression->lhs_ == nullptr && expression->rhs_ == nullptr) {
    if (op == "true") {
      tos_value_ = new IRT::ExpressionWrapper(new IRT::ConstExpression(1));
    } else if (op == "false") {
      tos_value_ = new IRT::ExpressionWrapper(new IRT::ConstExpression(0));
    }
  } else if (expression->lhs_ == nullptr) {
    auto wrapper = Accept(expression->rhs_);
    tos_value_ = new IRT::NegativeConditionalWrapper(wrapper);
  } else {
    auto lhs = Accept(expression->lhs_);
    auto rhs = Accept(expression->rhs_);

    if (op == "&&") {
      tos_value_ = new IRT::AndConditionalWrapper(lhs, rhs);
    } else if (op == "||") {
      tos_value_ = new IRT::OrConditionalWrapper(lhs, rhs);
    } else if (op == "==") {
      tos_value_ = new IRT::RelativeConditionalWrapper(
          IRT::LogicOperatorType::EQ, lhs->ToExpression(), rhs->ToExpression());
    } else if (op == ">") {
      tos_value_ = new IRT::RelativeConditionalWrapper(
          IRT::LogicOperatorType::GT, lhs->ToExpression(), rhs->ToExpression());
    } else if (op == "<") {
      tos_value_ = new IRT::RelativeConditionalWrapper(
          IRT::LogicOperatorType::LT, lhs->ToExpression(), rhs->ToExpression());
    } else if (op == ">=") {
      tos_value_ = new IRT::RelativeConditionalWrapper(
          IRT::LogicOperatorType::GE, lhs->ToExpression(), rhs->ToExpression()
          );
    } else if (op == "<=") {
      tos_value_ = new IRT::RelativeConditionalWrapper(
          IRT::LogicOperatorType::LE, lhs->ToExpression(), rhs->ToExpression()
      );
    } else if (op == "!=") {
      tos_value_ = new IRT::RelativeConditionalWrapper(
          IRT::LogicOperatorType::NE, lhs->ToExpression(), rhs->ToExpression()
      );
    }
  }
}

void IRTreeBuildVisitor::Visit(ArithmeticalExpression* expression) {
  const std::string& op = expression->operation_;

  if (expression->lhs_ == nullptr) {
    auto lhs = new IRT::ExpressionWrapper(new IRT::ConstExpression(0));
    auto rhs = Accept(expression->rhs_);

    tos_value_ = new IRT::ExpressionWrapper(
        new IRT::BinopExpression(IRT::BinaryOperatorType::MINUS,
                                 lhs->ToExpression(), rhs->ToExpression()));
  } else {
    auto lhs = Accept(expression->lhs_);
    auto rhs = Accept(expression->rhs_);

    if (op == "+") {
      tos_value_ = new IRT::ExpressionWrapper(
          new IRT::BinopExpression(IRT::BinaryOperatorType::PLUS,
                                   lhs->ToExpression(), rhs->ToExpression()));
    } else if (op == "-") {
      tos_value_ = new IRT::ExpressionWrapper(
          new IRT::BinopExpression(IRT::BinaryOperatorType::MINUS,
                                   lhs->ToExpression(), rhs->ToExpression()));
    } else if (op == "*") {
      tos_value_ = new IRT::ExpressionWrapper(
          new IRT::BinopExpression(IRT::BinaryOperatorType::MUL,
                                   lhs->ToExpression(), rhs->ToExpression()));
    } else if (op == "/") {
      tos_value_ = new IRT::ExpressionWrapper(
          new IRT::BinopExpression(IRT::BinaryOperatorType::DIV,
                                   lhs->ToExpression(), rhs->ToExpression()));
    } else if (op == "%") {
      tos_value_ = new IRT::ExpressionWrapper(
          new IRT::BinopExpression(IRT::BinaryOperatorType::MOD,
                                   lhs->ToExpression(), rhs->ToExpression()));
    }
  }
}

void IRTreeBuildVisitor::Visit(NewVariableExpression* expression) {
  auto expr =
      CreateObject(new PrimitiveSimpleObject(expression->variable_type_));

  tos_value_ = new IRT::ExpressionWrapper(expr);
}

void IRTreeBuildVisitor::Visit(VariableExpression* expression) {
  auto address = current_frame_->GetAddress(expression->variable_name_);
  tos_value_ = new IRT::ExpressionWrapper(address);
}

void IRTreeBuildVisitor::Visit(NumeralExpression* expression) {
  tos_value_ =
      new IRT::ExpressionWrapper(new IRT::ConstExpression(expression->value_));
}

void IRTreeBuildVisitor::Visit(MethodDeclaration* method_declaration) {
  current_layer_ = tree_->layer_mapping_[Symbol(
      current_classname_ + "$" + method_declaration->method_name_)];
  offsets_.push(0);

  std::string method_name = current_layer_->class_symbol_.GetName() +
                            "_" + method_declaration->method_name_;

  current_frame_ = new IRT::FrameTranslator(
      method_name, current_layer_->class_symbol_.GetName());
  frame_translator_[method_name] = current_frame_;

  if (method_declaration->formals_) {
    method_declaration->formals_->Accept(this);
  } else {
    current_frame_->AddArgumentAddress("this");
  }

  current_frame_->AddReturnAddress();

  auto statements_ir = Accept(method_declaration->list_of_statements_);

  if (statements_ir) {
    tos_value_ = new IRT::StatementWrapper(
        new IRT::SeqStatement(new IRT::LabelStatement(IRT::Label(method_name)),
                              statements_ir->ToStatement()));
  } else {
    throw std::runtime_error("Empty list of statements of method " + method_name);
  }
  method_trees_.emplace(method_name, std::make_pair(tos_value_->ToStatement(), current_frame_));
}

void IRTreeBuildVisitor::Visit(VariableDeclaration* variable_declaration) {
  tos_value_ = nullptr;
  if (variable_declaration->type_->type_name_.back() != ']') {
    current_frame_->AddLocalVariable(variable_declaration->variable_name_);
    if (variable_declaration->variable_name_ != "int" &&
        variable_declaration->variable_name_ != "boolean" &&
        variable_declaration->variable_name_ != "void") {
      auto expr =
          current_frame_->GetAddress(variable_declaration->variable_name_);
      IRT::Expression* value =
          CreateObject(new PrimitiveSimpleObject(variable_declaration->type_));

      tos_value_ =
          new IRT::StatementWrapper(new IRT::MoveStatement(expr, value));
    }
  } else {
    current_frame_->AddLocalVariable(variable_declaration->variable_name_);
  }
}

void IRTreeBuildVisitor::Visit(ClassDeclaration* class_declaration) {
  current_classname_ = class_declaration->class_name_;

  class_declaration->declarations_->Accept(this);
}

void IRTreeBuildVisitor::Visit(MainClass* main_class) {
  current_classname_ = main_class->main_class_name_;

  main_class->main_->Accept(this);
  main_class->declarations_->Accept(this);
}

void IRTreeBuildVisitor::Visit(MethodInvocation* method_invocation) {
  auto* irt_expressions = new IRT::ExpressionList();

  auto address = current_frame_->GetAddress(method_invocation->call_from_);
  irt_expressions->Add((new IRT::ExpressionWrapper(address))->ToExpression());

  if (method_invocation->arguments_list_ != nullptr) {
    for (auto expr : method_invocation->arguments_list_->list_of_expressions_) {
      irt_expressions->Add(Accept(expr)->ToExpression());
    }
  }

  Symbol class_name;
  if (method_invocation->call_from_ == "this") {
    class_name = current_layer_->class_symbol_;
  } else {
    const Symbol& symbol = Symbol(method_invocation->call_from_);

    class_name = Symbol(TypeResolving(symbol));
  }

  tos_value_ = new IRT::ExpressionWrapper(new IRT::CallExpression(
      new IRT::NameExpression(IRT::Label(
          class_name.GetName() + "_" + method_invocation->method_name_)),
      irt_expressions));
}

void IRTreeBuildVisitor::Visit(Formals* formals) {
  current_frame_->AddArgumentAddress("this");
  for (const auto& formal : formals->formals_) {
    current_frame_->AddArgumentAddress(formal.second);
  }
}

void IRTreeBuildVisitor::Visit(Program* program) {
  program->main_class_->Accept(this);
  program->class_declarations_->Accept(this);
}

void IRTreeBuildVisitor::Visit(Lvalue* lvalue) {
  if (lvalue->code_ == lvalue->VAR) {
    auto variable = current_frame_->GetAddress(lvalue->variable_name_);
    tos_value_ = new IRT::ExpressionWrapper(variable);
  } else if (lvalue->code_ == lvalue->ARR) {
    lvalue->array_access_expression_->Accept(this);
  } else if (lvalue->code_ == lvalue->FIELD) {
    lvalue->field_access_->Accept(this);
  }
}

void IRTreeBuildVisitor::Visit(FieldAccess* field_access) {
  std::cerr << "IR of field access is not implemented" << std::endl;
  exit(1);
}

////////////////////////////////////////////////////////////////////////////////

void IRTreeBuildVisitor::Visit(MethodExpression* method_expression) {}

void IRTreeBuildVisitor::Visit(Type* type) {}

void IRTreeBuildVisitor::Visit(ArrayType* array_type) {}

////////////////////////////////////////////////////////////////////////////////

void IRTreeBuildVisitor::PreVisit(Program* program) {}

void IRTreeBuildVisitor::PreVisit(MainClass* main_class) {}

void IRTreeBuildVisitor::PreVisit(ClassDeclaration* class_declaration) {}

void IRTreeBuildVisitor::PreVisit(ListOfStatements* list_of_statements) {}

void IRTreeBuildVisitor::PreVisit(VariableDeclaration* variable_declaration) {}

void IRTreeBuildVisitor::PreVisit(MethodDeclaration* method_declaration) {}
