#include "NewFunctionProcessingVisitor.h"

NewFunctionProcessingVisitor::NewFunctionProcessingVisitor(
    NewScopeLayerTree* tree, NewScopeLayer* main_layer,
    const std::shared_ptr<Method>& main_func_ptr)
    : tree_(tree),
      root_layer_(main_layer),
      frame_(main_func_ptr),
      is_returned_(false) {
  tree_->root_->PrepareTraversing();

  current_layer_ = root_layer_;
  tos_value_ = 0;
  offsets_.push(0);

  std::vector<int> fields;
  int index = -1;

  // TODO Arrays
  const auto& fields_map = std::get<0>(
      tree_->class_symbols_table_[Symbol(main_func_ptr->owner_class_)]);
  fields.reserve(fields_map.size());
  for (auto&& field : fields_map) {
    fields.emplace_back(field.second.second);

    table_.CreateVariable(field.first);
    table_.Put(field.first, index);
    --index;
  }

  frame_.SetFields(fields);
}

void NewFunctionProcessingVisitor::TraverseToChildByIndex() {
  // TODO this thing starts annoying me
  if (current_layer_->traverse_index >= current_layer_->children_.size()) {
    throw std::runtime_error("Error while traversing...");
  }

  ++current_layer_->traverse_index;
  current_layer_ =
      current_layer_->children_[current_layer_->traverse_index - 1];
}

////////////////////////////////////////////////////////////////////////////////

void NewFunctionProcessingVisitor::Visit(AssertStatement *assert_statement) {
  if (!Accept(assert_statement->expression_)) {
    throw std::runtime_error("Assert failed");
  }
}

void NewFunctionProcessingVisitor::Visit(AssignmentStatement* statement) {
  auto value = Accept(statement->expression_);
  // TODO Arrays and this
  int index = table_.Get(Symbol(statement->lvalue_->variable_name_));
  frame_.Set(index, value);
}

void NewFunctionProcessingVisitor::Visit(IfStatement* statement) {
  if (statement->else_statement_ == nullptr) {
    if (Accept(statement->if_statement_)) {
      TraverseToChildByIndex();

      offsets_.push(0);
      frame_.AllocScope();
      table_.BeginScope();

      statement->if_statement_->Accept(this);

      offsets_.pop();
      size_t index = offsets_.top();
      offsets_.pop();
      offsets_.push(index + 1);

      current_layer_ = current_layer_->parent_;

      frame_.DeallocScope();
      table_.EndScope();
    }
  } else {
    if (Accept(statement->if_statement_)) {
      TraverseToChildByIndex();

      offsets_.push(0);
      frame_.AllocScope();
      table_.BeginScope();

      statement->if_statement_->Accept(this);

      offsets_.pop();
      size_t index = offsets_.top();
      offsets_.pop();
      offsets_.push(index + 2);

      current_layer_ = current_layer_->parent_;

      frame_.DeallocScope();
      table_.EndScope();
    }
  }
}

void NewFunctionProcessingVisitor::Visit(ScopeListOfStatements* scope_list_of_statements) {
  TraverseToChildByIndex();

  offsets_.push(0);
  frame_.AllocScope();
  table_.BeginScope();

  scope_list_of_statements->list_of_statements_->Accept(this);

  offsets_.pop();
  size_t index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);

  current_layer_ = current_layer_->parent_;

  frame_.DeallocScope();
  table_.EndScope();
}

void NewFunctionProcessingVisitor::Visit(ListOfStatements* list_of_statements) {
  for (auto&& statement : list_of_statements->list_of_statements_) {
    if (!is_returned_) {
      statement->Accept(this);
    }
  }
}

void NewFunctionProcessingVisitor::Visit(WhileStatement* statement) {
  while (Accept(statement->expression_)) {
    TraverseToChildByIndex();

    offsets_.push(0);
    frame_.AllocScope();
    table_.BeginScope();

    statement->statement_->Accept(this);

    offsets_.pop();
    current_layer_ = current_layer_->parent_;
    frame_.DeallocScope();
    table_.EndScope();
  }
  size_t  index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);
}

void NewFunctionProcessingVisitor::Visit(ArithmeticalExpression* expression) {
  if (expression->lhs_ == nullptr) {
    int rhs = Accept(expression->rhs_);

    tos_value_ = -rhs;
  } else {
    int lhs = Accept(expression->lhs_);
    int rhs = Accept(expression->rhs_);

    if (expression->operation_ == "+") {
      tos_value_ = lhs + rhs;
    }
    if (expression->operation_ == "-") {
      tos_value_ = lhs - rhs;
    }
    if (expression->operation_ == "*") {
      tos_value_ = lhs * rhs;
    }
    if (expression->operation_ == "/") {
      tos_value_ = lhs / rhs;
    }
    if (expression->operation_ == "%") {
      tos_value_ = lhs % rhs;
    }
  }
}

void NewFunctionProcessingVisitor::Visit(LogicalExpression* expression) {
  if (expression->operation_ == "true") {
    tos_value_ = 1;
  }
  if (expression->operation_ == "false") {
    tos_value_ = 0;
  }
  if (expression->lhs_ == nullptr) {
    int value = Accept(expression->rhs_);
    tos_value_ = !value;
  } else {
    int lhs = Accept(expression->lhs_);
    int rhs = Accept(expression->rhs_);
    if (expression->operation_ == "&&") {
      tos_value_ = lhs && rhs;
    }
    if (expression->operation_ == "||") {
      tos_value_ = lhs || rhs;
    }
    if (expression->operation_ == "<") {
      tos_value_ = lhs < rhs;
    }
    if (expression->operation_ == "<=") {
      tos_value_ = lhs <= rhs;
    }
    if (expression->operation_ == ">") {
      tos_value_ = lhs > rhs;
    }
    if (expression->operation_ == ">=") {
      tos_value_ = lhs >= rhs;
    }
    if (expression->operation_ == "==") {
      tos_value_ = lhs == rhs;
    }
    if (expression->operation_ == "!=") {
      tos_value_ = lhs != rhs;
    }
  }
}

void NewFunctionProcessingVisitor::Visit(VariableExpression* expression) {
  int index = table_.Get(Symbol(expression->variable_name_));
  tos_value_ = frame_.Get(index);
}

void NewFunctionProcessingVisitor::Visit(NumeralExpression* expression) {
  tos_value_ = expression->value_;
}

void NewFunctionProcessingVisitor::Visit(MethodDeclaration* method_declaration) {
  method_declaration->formals_->Accept(this);
  method_declaration->list_of_statements_->Accept(this);
}

void NewFunctionProcessingVisitor::Visit(VariableDeclaration* variable_declaration) {
  // TODO Arrays
  size_t index = frame_.AllocVariable();
  table_.CreateVariable(Symbol(variable_declaration->variable_name_));
  table_.Put(Symbol(variable_declaration->variable_name_), index);
}

void NewFunctionProcessingVisitor::Visit(MethodInvocation* method_invocation) {
  std::cerr << method_invocation->method_name_ << " called!" << std::endl;



  // TODO
}

void NewFunctionProcessingVisitor::Visit(Formals* formals) {
  int index = -frame_.GetFieldSize() - 1;

  for (auto&& formal : formals->formals_) {
    table_.CreateVariable(Symbol(formal.second));
    table_.Put(Symbol(formal.second), index);
  }
}

////////////////////////////////////////////////////////////////////////////////

void NewFunctionProcessingVisitor::Visit(ArrayAccessExpression* expression) {}
void NewFunctionProcessingVisitor::Visit(LengthExpression* expression) {}
void NewFunctionProcessingVisitor::Visit(NewArrayExpression* expression) {}
void NewFunctionProcessingVisitor::Visit(NewVariableExpression* expression) {}
void NewFunctionProcessingVisitor::Visit(FieldAccess* field_access) {}
void NewFunctionProcessingVisitor::Visit(MethodExpression* method_expression) {}
void NewFunctionProcessingVisitor::Visit(Lvalue* lvalue) {}

void NewFunctionProcessingVisitor::Visit(Type* type) {}
void NewFunctionProcessingVisitor::Visit(ArrayType* array_type) {}

void NewFunctionProcessingVisitor::Visit(Program* program) {}

void NewFunctionProcessingVisitor::Visit(ReturnStatement* statement) {}
void NewFunctionProcessingVisitor::Visit(PrintStatement* statement) {}
void NewFunctionProcessingVisitor::Visit(MainClass* main_class) {}
void NewFunctionProcessingVisitor::Visit(ClassDeclaration* class_declaration) {}

////////////////////////////////////////////////////////////////////////////////

void NewFunctionProcessingVisitor::PreVisit(Program* program) {}
void NewFunctionProcessingVisitor::PreVisit(MainClass* main_class) {}
void NewFunctionProcessingVisitor::PreVisit(
    ClassDeclaration* class_declaration) {}
void NewFunctionProcessingVisitor::PreVisit(
    ListOfStatements* list_of_statements) {}
void NewFunctionProcessingVisitor::PreVisit(
    VariableDeclaration* variable_declaration) {}
void NewFunctionProcessingVisitor::PreVisit(
    MethodDeclaration* method_declaration) {}
