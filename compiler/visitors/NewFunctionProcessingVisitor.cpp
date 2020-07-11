#include "NewFunctionProcessingVisitor.h"

#include "../classes/Type.h"

NewFunctionProcessingVisitor::NewFunctionProcessingVisitor(
    NewScopeLayerTree* tree, NewScopeLayer* main_layer,
    const std::shared_ptr<Method>& main_func_ptr, const Symbol& this_main)
    : tree_(tree),
      root_layer_(main_layer),
      frame_(main_func_ptr),
      is_returned_(false) {
  tree_->root_->PrepareTraversing();

  // TODO wtf
  this_ = this_main;

  current_layer_ = root_layer_;
  tos_value_ = new VariableValue(new PrimitiveSimpleObject(new Type("int")), 0);
  offsets_.push(0);

  std::vector<Value*> fields;
  int index = -1;

  ClassStorage& storage = ClassStorage::GetInstance();

  for (auto&& field : storage.GetFields(this_)) {
    fields.emplace_back(field.second);

    table_.CreateVariable(field.first);
    table_.Put(field.first, index);
    --index;
  }

  frame_.SetFields(fields);
}

void NewFunctionProcessingVisitor::TraverseToChildByIndex() {
  if (current_layer_->traverse_index >= current_layer_->children_.size()) {
    throw std::runtime_error("Error while traversing...");
  }

  ++current_layer_->traverse_index;
  current_layer_ =
      current_layer_->children_[current_layer_->traverse_index - 1];
}

////////////////////////////////////////////////////////////////////////////////

void NewFunctionProcessingVisitor::Visit(AssertStatement* assert_statement) {
  if (!Accept(assert_statement->expression_)->GetValue()) {
    throw std::runtime_error("Assert failed");
  }
}

void NewFunctionProcessingVisitor::Visit(AssignmentStatement* statement) {
  auto value = Accept(statement->expression_);
  if (statement->lvalue_->code_ == Lvalue::CODE::ARR) {
    int index = table_.Get(
        Symbol(statement->lvalue_->array_access_expression_->array_indent_));
    int array_index =
        Accept(statement->lvalue_->array_access_expression_->index_expression_)
            ->GetValue();

    dynamic_cast<ArrayValue*>(frame_.Get(index))
        ->SetAtIndex(value, array_index);
  } else {
    int index = table_.Get(Symbol(statement->lvalue_->variable_name_));

    // TODO fields?
    frame_.Set(index, value);
  }
}

void NewFunctionProcessingVisitor::Visit(IfStatement* statement) {
  if (statement->else_statement_ == nullptr) {
    if (Accept(statement->if_statement_)->GetValue()) {
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
    if (Accept(statement->if_statement_)->GetValue()) {
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

void NewFunctionProcessingVisitor::Visit(
    ScopeListOfStatements* scope_list_of_statements) {
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
  while (Accept(statement->expression_)->GetValue()) {
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
  size_t index = offsets_.top();
  offsets_.pop();
  offsets_.push(index + 1);
}

void NewFunctionProcessingVisitor::Visit(ArrayAccessExpression* expression) {
  int array_index = Accept(expression->index_expression_)->GetValue();
  int index = table_.Get(Symbol(expression->array_indent_));
  tos_value_ =
      dynamic_cast<ArrayValue*>(frame_.Get(index))->AtIndex(array_index);
}

void NewFunctionProcessingVisitor::Visit(NewArrayExpression* expression) {
  auto new_arr = new ArrayValue(new PrimitiveArrayObject(
      new PrimitiveSimpleObject(expression->type_name_)));

  size_t size = Accept(expression->length_)->GetValue();
  new_arr->Resize(size);
  tos_value_ = new_arr;
}

void NewFunctionProcessingVisitor::Visit(NewVariableExpression* expression) {
  tos_value_ = new VariableValue(new PrimitiveSimpleObject(
      new Type(expression->variable_type_->type_name_)));
}

void NewFunctionProcessingVisitor::Visit(LengthExpression* expression) {
  int index = table_.Get(Symbol(expression->variable_name_));
  int size = dynamic_cast<ArrayValue*>(frame_.Get(index))->GetSize();
  tos_value_ =
      new VariableValue(new PrimitiveSimpleObject(new Type("int")), size);
}

void NewFunctionProcessingVisitor::Visit(ArithmeticalExpression* expression) {
  if (expression->lhs_ == nullptr) {
    auto rhs = Accept(expression->rhs_)->GetValue();

    tos_value_ =
        new VariableValue(new PrimitiveSimpleObject(new Type("int")), -rhs);
  } else {
    auto lhs = Accept(expression->lhs_)->GetValue();
    auto rhs = Accept(expression->rhs_)->GetValue();
    int result = 0;

    if (expression->operation_ == "+") {
      result = lhs + rhs;
    }
    if (expression->operation_ == "-") {
      result = lhs - rhs;
    }
    if (expression->operation_ == "*") {
      result = lhs * rhs;
    }
    if (expression->operation_ == "/") {
      result = lhs / rhs;
    }
    if (expression->operation_ == "%") {
      result = lhs % rhs;
    }

    tos_value_ =
        new VariableValue(new PrimitiveSimpleObject(new Type("int")), result);
  }
}

void NewFunctionProcessingVisitor::Visit(LogicalExpression* expression) {
  if (expression->operation_ == "true") {
    tos_value_ =
        new VariableValue(new PrimitiveSimpleObject(new Type("boolean")), 1);
  }
  if (expression->operation_ == "false") {
    tos_value_ =
        new VariableValue(new PrimitiveSimpleObject(new Type("boolean")), 0);
  }
  if (expression->lhs_ == nullptr) {
    auto value = Accept(expression->rhs_)->GetValue();
    tos_value_ = new VariableValue(
        new PrimitiveSimpleObject(new Type("boolean")), !value);
  } else {
    auto lhs = Accept(expression->lhs_)->GetValue();
    auto rhs = Accept(expression->rhs_)->GetValue();
    bool result = false;
    if (expression->operation_ == "&&") {
      result = lhs && rhs;
    }
    if (expression->operation_ == "||") {
      result = lhs || rhs;
    }
    if (expression->operation_ == "<") {
      result = lhs < rhs;
    }
    if (expression->operation_ == "<=") {
      result = lhs <= rhs;
    }
    if (expression->operation_ == ">") {
      result = lhs > rhs;
    }
    if (expression->operation_ == ">=") {
      result = lhs >= rhs;
    }
    if (expression->operation_ == "==") {
      result = lhs == rhs;
    }
    if (expression->operation_ == "!=") {
      result = lhs != rhs;
    }

    tos_value_ = new VariableValue(
        new PrimitiveSimpleObject(new Type("boolean")), result);
  }
}

void NewFunctionProcessingVisitor::Visit(VariableExpression* expression) {
  int index = table_.Get(Symbol(expression->variable_name_));
  tos_value_ = frame_.Get(index);
}

void NewFunctionProcessingVisitor::Visit(NumeralExpression* expression) {
  tos_value_ = new VariableValue(new PrimitiveSimpleObject(new Type("int")),
                                 expression->value_);
}

void NewFunctionProcessingVisitor::Visit(
    MethodDeclaration* method_declaration) {
  method_declaration->formals_->Accept(this);
  method_declaration->list_of_statements_->Accept(this);
}

void NewFunctionProcessingVisitor::Visit(
    VariableDeclaration* variable_declaration) {
  size_t index;

  if (variable_declaration->type_->type_name_.back() != ']') {
    index = frame_.AllocVariable(
        new PrimitiveSimpleObject(variable_declaration->type_));
  } else {
    index = frame_.AllocVariable(new PrimitiveArrayObject(
        dynamic_cast<ArrayType*>(variable_declaration->type_)));
  }

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
    --index;
  }
}

void NewFunctionProcessingVisitor::Visit(ReturnStatement* statement) {
  if (frame_.HasParent()) {
    frame_.SetParentReturnValue(Accept(statement->expression_));
  }

  is_returned_ = true;
}

void NewFunctionProcessingVisitor::Visit(PrintStatement* statement) {
  std::cout << Accept(statement->expression_)->GetValue() << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

void NewFunctionProcessingVisitor::Visit(FieldAccess* field_access) {
  // TODO
}
void NewFunctionProcessingVisitor::Visit(MethodExpression* method_expression) {
  // TODO
}

void NewFunctionProcessingVisitor::Visit(Lvalue* lvalue) {}

void NewFunctionProcessingVisitor::Visit(Type* type) {}
void NewFunctionProcessingVisitor::Visit(ArrayType* array_type) {}

void NewFunctionProcessingVisitor::Visit(Program* program) {}

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
