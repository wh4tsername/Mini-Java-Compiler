#include "FunctionProcessingVisitor.h"

// @TODO Multiple classes impl

FunctionProcessingVisitor::FunctionProcessingVisitor(
    ScopeLayer* function_scope, std::shared_ptr<Method> function)
    : root_layer_(function_scope), frame_(std::move(function)), tree_(nullptr) {
  current_layer_ = root_layer_;
  offsets_.push(0);
  tos_value_ = 0;
}

void FunctionProcessingVisitor::SetTree(ScopeLayerTree* tree) { tree_ = tree; }

void FunctionProcessingVisitor::SetParams(const std::vector<int>& params) {
  frame_.SetParameters(params);
}

FrameEmulator& FunctionProcessingVisitor::GetFrame() { return frame_; }

void FunctionProcessingVisitor::Visit(ArrayAccessExpression* expression) {
  // @TODO DO SMTH
}

void FunctionProcessingVisitor::Visit(ArithmeticalExpression* expression) {
  const std::string& op = expression->operation_;
  if (op == "@") {
    tos_value_ = -1 * Accept(expression->rhs_);
  } else if (op == "+") {
    tos_value_ = Accept(expression->lhs_) + Accept(expression->rhs_);
  } else if (op == "-") {
    tos_value_ = Accept(expression->lhs_) - Accept(expression->rhs_);
  } else if (op == "*") {
    tos_value_ = Accept(expression->lhs_) * Accept(expression->rhs_);
  } else if (op == "/") {
    tos_value_ = Accept(expression->lhs_) / Accept(expression->rhs_);
  } else if (op == "%") {
    tos_value_ = Accept(expression->lhs_) % Accept(expression->rhs_);
  }
}

void FunctionProcessingVisitor::Visit(LogicalExpression* expression) {
  const std::string& op = expression->operation_;
  if (op == "true") {
    tos_value_ = 1;
  } else if (op == "false") {
    tos_value_ = 0;
  } else if (op == "!") {
    tos_value_ = !Accept(expression->rhs_);
  } else if (op == "&&") {
    tos_value_ = Accept(expression->lhs_) && Accept(expression->rhs_);
  } else if (op == "||") {
    tos_value_ = Accept(expression->lhs_) || Accept(expression->rhs_);
  } else if (op == "<") {
    tos_value_ = Accept(expression->lhs_) < Accept(expression->rhs_);
  } else if (op == ">") {
    tos_value_ = Accept(expression->lhs_) > Accept(expression->rhs_);
  } else if (op == "<=") {
    tos_value_ = Accept(expression->lhs_) <= Accept(expression->rhs_);
  } else if (op == ">=") {
    tos_value_ = Accept(expression->lhs_) >= Accept(expression->rhs_);
  } else if (op == "==") {
    tos_value_ = Accept(expression->lhs_) == Accept(expression->rhs_);
  } else if (op == "!=") {
    tos_value_ = Accept(expression->lhs_) != Accept(expression->rhs_);
  }
}

void FunctionProcessingVisitor::Visit(LengthExpression* expression) {
  // @TODO
}

void FunctionProcessingVisitor::Visit(NewArrayExpression* expression) {
  // @TODO
}

void FunctionProcessingVisitor::Visit(NewVariableExpression* expression) {
  // @TODO
}

void FunctionProcessingVisitor::Visit(NumeralExpression* expression) {
  tos_value_ = expression->value_;
}

void FunctionProcessingVisitor::Visit(VariableExpression* expression) {
  int index = table_.Get(Symbol(expression->variable_name_));
  tos_value_ = frame_.Get(index);
}

void FunctionProcessingVisitor::Visit(MethodInvocation* method_invocation) {
  std::cerr << "Function: " << method_invocation->method_name_ << " called"
            << std::endl;
  auto function_type =
      current_layer_->Get(Symbol(method_invocation->method_name_));

  std::shared_ptr<Method> func_converted =
      std::dynamic_pointer_cast<Method>(function_type);

  if (func_converted == nullptr) {
    throw std::runtime_error("Function not defined");
  }

  std::vector<int> params;

  if (method_invocation->arguments_list_) {
    for (auto& param :
         method_invocation->arguments_list_->list_of_expressions_) {
      params.emplace_back(Accept(param));
    }
  }

  FunctionProcessingVisitor new_visitor(
      tree_->GetFunctionScope(Symbol(method_invocation->method_name_)),
      func_converted);

  new_visitor.SetParams(params);
  new_visitor.SetTree(tree_);

  new_visitor.GetFrame().SetParentFrame(&frame_);
  new_visitor.Visit(FunctionStorage::GetInstance().Get(
      Symbol(method_invocation->method_name_)));

  tos_value_ = frame_.GetReturnValue();
}

void FunctionProcessingVisitor::Visit(
    VariableDeclaration* variable_declaration) {
  // @TODO What will happen, if we want to alloc array or class obj
  size_t index = frame_.AllocVariable();
  table_.CreateVariable(Symbol(variable_declaration->variable_name_));
  table_.Put(Symbol(variable_declaration->variable_name_), index);
}

void FunctionProcessingVisitor::Visit(MethodExpression* method_expression) {}

void FunctionProcessingVisitor::Visit(Formals* formals) {
  // @TODO What if we want to pass arr as arg
  int index = -1;
  for (auto& formal : formals->formals_) {
    table_.CreateVariable(Symbol(formal.second));
    table_.Put(Symbol(formal.second), index);
    --index;
  }
}

void FunctionProcessingVisitor::Visit(Lvalue* lvalue) {}

void FunctionProcessingVisitor::Visit(Type* type) {}

void FunctionProcessingVisitor::Visit(ArrayType* array_type) {}

void FunctionProcessingVisitor::Visit(Program* program) {}

void FunctionProcessingVisitor::Visit(ListOfStatements* list_of_statements) {
  for (auto& statement : list_of_statements->list_of_statements_) {
    if (!returned_) {
      statement->Accept(this);
    }
  }
}

void FunctionProcessingVisitor::Visit(WhileStatement* statement) {
  // @TODO while
}

void FunctionProcessingVisitor::Visit(IfStatement* statement) {
  int expression_res = Accept(statement->expression_);
  if (expression_res == 1) {
//    current_layer_ = current_layer_->GetChild(offsets_.top());
//    offsets_.push(0);
//    frame_.AllocScope();
//    table_.BeginScope();
    statement->if_statement_->Accept(this);
//    offsets_.pop();
//    size_t index = offsets_.top();
//    offsets_.pop();
//    offsets_.push(index + 2);
//    current_layer_ = current_layer_->GetParent();
//    frame_.DeallocScope();
//    table_.EndScope();
  } else {
    int value = offsets_.top();

    offsets_.push(0);

    current_layer_ = current_layer_->GetChild(value + 1);
    frame_.AllocScope();
    table_.BeginScope();
    statement->else_statement_->Accept(this);
    offsets_.pop();
    offsets_.pop();
    offsets_.push(value + 2);

    current_layer_ = current_layer_->GetParent();
    frame_.DeallocScope();
    table_.EndScope();
  }
}

void FunctionProcessingVisitor::Visit(ReturnStatement* statement) {
  if (frame_.HasParent()) {
    frame_.SetParentReturnValue(Accept(statement->expression_));
  }

  returned_ = true;
}

void FunctionProcessingVisitor::Visit(PrintStatement* statement) {
  int value = Accept(statement->expression_);

  std::cout << value << std::endl;
}

void FunctionProcessingVisitor::Visit(AssignmentStatement* statement) {
  int value = Accept(statement->expression_);
  int index = 0;
  if (statement->lvalue_->code_ == Lvalue::CODE::ARR) {
    // TODO actual array access :)
  } else if (statement->lvalue_->code_ == Lvalue::CODE::VAR) {
    const Symbol &symbol = Symbol(statement->lvalue_->variable_name_);
    index = table_.Get(symbol);
    frame_.Set(index, value);
  } else if (statement->lvalue_->code_ == Lvalue::CODE::FIELD) {
    // TODO
  } else {
    throw std::runtime_error("Incorrect lvalue code!");
  }
}

void FunctionProcessingVisitor::Visit(AssertStatement* statement) {
  assert(Accept(statement->expression_));
}

void FunctionProcessingVisitor::Visit(MethodDeclaration* method_declaration) {
  current_layer_->SetFields(current_layer_->GetParent()->GetFields());

  if (method_declaration->formals_) {
    method_declaration->formals_->Accept(this);
  }
  if (method_declaration->list_of_statements_) {
    method_declaration->list_of_statements_->Accept(this);
  }
}

void FunctionProcessingVisitor::Visit(MainClass* main_class) {}

void FunctionProcessingVisitor::Visit(ClassDeclaration* class_declaration) {}

void FunctionProcessingVisitor::Visit(
    ScopeListOfStatements* scope_list_of_statements) {
  std::cerr << "Going deeper..." << std::endl;

  current_layer_ = current_layer_->GetChild(offsets_.top());

  current_layer_->SetFields(current_layer_->GetParent()->GetFields());

  offsets_.push(0);
  frame_.AllocScope();
  table_.BeginScope();
  scope_list_of_statements->list_of_statements_->Accept(this);

  offsets_.pop();
  size_t index = offsets_.top();

  offsets_.pop();
  offsets_.push(index + 1);

  current_layer_ = current_layer_->GetParent();
  frame_.DeallocScope();
  table_.EndScope();
}

void FunctionProcessingVisitor::Visit(FieldAccess* field_access) {
  // TODO field access
}
