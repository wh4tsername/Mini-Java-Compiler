#include "TypeCheckingVisitor.h"

TypeCheckingVisitor::TypeCheckingVisitor(NewScopeLayerTree& tree)
    : tree_(tree), current_layer_(tree.root_), type_count_(4) {
  tree_.root_->PrepareTraversing();
}

void TypeCheckingVisitor::TraverseToChildByClassSymbol(const Symbol& symbol) {
  for (auto& child : current_layer_->children_) {
    if (child->class_symbol_ == symbol) {
      current_layer_ = child;
      break;
    }
  }
}

void TypeCheckingVisitor::TraverseToChildByMethodSymbol(const Symbol& symbol) {
  for (auto& child : current_layer_->children_) {
    if (child->name_ == symbol.GetName()) {
      current_layer_ = child;
      break;
    }
  }
}

void TypeCheckingVisitor::TraverseToChildByIndex() {
  if (current_layer_->traverse_index >= current_layer_->children_.size()) {
    throw std::runtime_error("Error while traversing...");
  }

  ++current_layer_->traverse_index;
  current_layer_ =
      current_layer_->children_[current_layer_->traverse_index - 1];
}

bool TypeCheckingVisitor::HasType(const std::string& type) {
  return type_system_.find(type) != type_system_.end();
}

////////////////////////////////////////////////////////////////////////////////

void TypeCheckingVisitor::Visit(Program* program) {
  PreVisit(program);

  if (program->class_declarations_) {
    Accept(program->class_declarations_);
  }

  Accept(program->main_class_);
}

void TypeCheckingVisitor::Visit(ListOfStatements* list_of_statements) {
  for (auto& statement : list_of_statements->list_of_statements_) {
    Accept(statement);
  }
}

void TypeCheckingVisitor::Visit(ClassDeclaration* class_declaration) {
  TraverseToChildByClassSymbol(Symbol(class_declaration->class_name_));

  Accept(class_declaration->declarations_);

  current_layer_ = current_layer_->parent_;
}

void TypeCheckingVisitor::Visit(MainClass* main_class) {
  TraverseToChildByClassSymbol(Symbol(main_class->main_class_name_));

  if (main_class->declarations_) {
    Accept(main_class->declarations_);
  }

  Accept(main_class->main_);

  current_layer_ = current_layer_->parent_;
}

void TypeCheckingVisitor::Visit(MethodDeclaration* method_declaration) {
  TraverseToChildByMethodSymbol(Symbol(method_declaration->method_name_));

  if (!HasType(method_declaration->type_->type_name_) &&
      method_declaration->type_->type_name_ != "void") {
    throw std::runtime_error("Unknown return value type");
  }

  if (method_declaration->formals_) {
    Accept(method_declaration->formals_);
  }

  Accept(method_declaration->list_of_statements_);

  current_layer_ = current_layer_->parent_;
}

void TypeCheckingVisitor::Visit(Formals* formals) {
  for (auto& formal : formals->formals_) {
    if (!HasType(formal.first->type_name_)) {
      throw std::runtime_error("Unknown type " + formal.first->type_name_ +
                               " of " + formal.second);
    }

    current_layer_->symbol_types_[Symbol(formal.second)] =
        type_system_[formal.first->type_name_];
  }
}

void TypeCheckingVisitor::Visit(
    ScopeListOfStatements* scope_list_of_statements) {
  TraverseToChildByIndex();

  Accept(scope_list_of_statements->list_of_statements_);

  current_layer_ = current_layer_->parent_;
}

void TypeCheckingVisitor::Visit(PrintStatement* statement) {
  int type_code = Accept(statement->expression_);
  if (type_code != type_system_["int"] &&
      type_code != type_system_["boolean"]) {
    throw std::runtime_error("Can't print such type");
  }
}

void TypeCheckingVisitor::Visit(AssertStatement* statement) {
  int type_code = Accept(statement->expression_);
  if (type_code != type_system_["boolean"]) {
    throw std::runtime_error("Can't assert expr with such type");
  }
}

void TypeCheckingVisitor::Visit(ReturnStatement* statement) {
  int type_code = Accept(statement->expression_);

  NewScopeLayer* current = current_layer_;
  while (current->parent_->parent_->parent_ != nullptr) {
    current = current->parent_;
  }

  const Symbol& method_symbol = current_layer_->method_symbol_;
  const Symbol& class_symbol = current->class_symbol_;
  std::string return_type =
      std::get<1>(tree_.class_symbols_table_[class_symbol])[method_symbol]
          ->return_type_;

  if (!HasType(return_type)) {
    throw std::runtime_error("Unknown return value type");
  }

  if (type_code != type_system_[return_type]) {
    throw std::runtime_error("Wrong return value type");
  }
}

////////////////////////////////////////////////////////////////////////////////

std::string TypeCheckingVisitor::UserTypeResolving(const Symbol& symbol) {
  NewScopeLayer* local_current = current_layer_;

  while (local_current->user_type_system_.find(symbol) ==
         local_current->user_type_system_.end()) {
    local_current = local_current->parent_;
  }

  return local_current->user_type_system_[symbol];
}

////////////////////////////////////////////////////////////////////////////////

void TypeCheckingVisitor::Visit(MethodInvocation* method_invocation) {
  Symbol class_name;

  if (method_invocation->call_from_ == "this") {
    class_name = current_layer_->class_symbol_;
  } else {
    const Symbol& symbol = Symbol(method_invocation->call_from_);

    class_name = Symbol(UserTypeResolving(symbol));
  }

  auto method_obj = std::get<1>(tree_.class_symbols_table_[class_name])[Symbol(
      method_invocation->method_name_)];

  if (method_invocation->arguments_list_) {
    const auto& args = method_invocation->arguments_list_->list_of_expressions_;
    for (size_t i = 0; i < args.size(); ++i) {
      int type_code = Accept(args[i]);

      if (type_code != type_system_[method_obj->types_[i]]) {
        throw std::runtime_error("Wrong argument type: " +
                                 method_obj->argument_names_[i]);
      }
    }
  }

  if (!HasType(method_obj->return_type_) &&
      method_obj->return_type_ != "void") {
    throw std::runtime_error("Unknown return value type");
  }

  tos_value_ = type_system_[method_obj->return_type_];
}

void TypeCheckingVisitor::Visit(FieldAccess* field_access) {
  auto& fields =
      std::get<0>(tree_.class_symbols_table_[current_layer_->class_symbol_]);
  auto& arr_fields =
      std::get<2>(tree_.class_symbols_table_[current_layer_->class_symbol_]);
  if (fields.find(Symbol(field_access->field_name_)) != fields.end()) {
    tos_value_ = type_system_[fields[Symbol(field_access->field_name_)].first];
  } else {
    tos_value_ =
        type_system_[arr_fields[Symbol(field_access->field_name_)].first];
  }
}

void TypeCheckingVisitor::Visit(AssignmentStatement* statement) {
  if (Accept(statement->lvalue_) != Accept(statement->expression_)) {
    throw std::runtime_error("Can't assign different types");
  }
}

void TypeCheckingVisitor::Visit(Lvalue* lvalue) {
  if (lvalue->code_ == lvalue->VAR) {
    const Symbol& symbol = Symbol(lvalue->variable_name_);
    NewScopeLayer* current = current_layer_;

    while (!current->HasArray(symbol) && !current->HasVariable(symbol) &&
        current->parent_->parent_ != nullptr) {
      current = current->parent_;
    }

    tos_value_ = current->symbol_types_[Symbol(lvalue->variable_name_)];
  } else if (lvalue->code_ == lvalue->ARR) {
    tos_value_ = Accept(lvalue->array_access_expression_);
  } else if (lvalue->code_ == lvalue->FIELD) {
    tos_value_ = Accept(lvalue->field_access_);
  }
}

void TypeCheckingVisitor::Visit(WhileStatement* statement) {
  if (Accept(statement->expression_) != type_system_["boolean"]) {
    throw std::runtime_error("Non-boolean expr in while condition");
  }

  Accept(statement->statement_);
}

void TypeCheckingVisitor::Visit(IfStatement* statement) {
  if (Accept(statement->expression_) != type_system_["boolean"]) {
    throw std::runtime_error("Non-boolean expr in if condition");
  }

  Accept(statement->if_statement_);

  if (statement->else_statement_) {
    Accept(statement->else_statement_);
  }
}

void TypeCheckingVisitor::Visit(VariableDeclaration* variable_declaration) {
  const std::string& type_name = variable_declaration->type_->type_name_;
  if (!HasType(type_name)) {
    throw std::runtime_error("Unknown type " + type_name + " of " +
                             variable_declaration->variable_name_);
  }

  current_layer_->symbol_types_[Symbol(variable_declaration->variable_name_)] =
      type_system_[type_name];
}

void TypeCheckingVisitor::Visit(VariableExpression* expression) {
  // can be arr or var
  const Symbol& symbol = Symbol(expression->variable_name_);
  NewScopeLayer* current = current_layer_;

  while (!current->HasArray(symbol) && !current->HasVariable(symbol) &&
      current->parent_->parent_ != nullptr) {
    current = current->parent_;
  }

  tos_value_ = current->symbol_types_[Symbol(expression->variable_name_)];
}

void TypeCheckingVisitor::Visit(NumeralExpression* expression) {
  tos_value_ = type_system_["int"];
}

void TypeCheckingVisitor::Visit(NewVariableExpression* expression) {
  tos_value_ = type_system_[expression->variable_type_->type_name_];
}

void TypeCheckingVisitor::Visit(NewArrayExpression* expression) {
  tos_value_ = type_system_[expression->type_name_->type_name_];
}

void TypeCheckingVisitor::Visit(LengthExpression* expression) {
  NewScopeLayer* layer =
      current_layer_->GetArrayLayer(Symbol(expression->variable_name_));

  if (layer->symbol_types_[Symbol(expression->variable_name_)] % 2 != 0) {
    throw std::runtime_error("Can't take length from non-array type");
  }

  tos_value_ = type_system_["int"];
}

void TypeCheckingVisitor::Visit(LogicalExpression* expression) {
  if (expression->operation_ == "&&" || expression->operation_ == "||" ||
      expression->operation_ == "!" || expression->operation_ == "true" ||
      expression->operation_ == "false") {
    if (expression->lhs_) {
      int type_code = Accept(expression->lhs_);

      if (type_code != type_system_["boolean"]) {
        throw std::runtime_error("Non-boolean type in logical expression");
      }
    }
    if (expression->rhs_) {
      int type_code = Accept(expression->rhs_);

      if (type_code != type_system_["boolean"]) {
        throw std::runtime_error("Non-boolean type in logical expression");
      }
    }
  } else {
    int type_code = Accept(expression->lhs_);

    if (type_code != type_system_["int"]) {
      throw std::runtime_error("Non-int type in comparison");
    }

    type_code = Accept(expression->rhs_);

    if (type_code != type_system_["int"]) {
      throw std::runtime_error("Non-int type in comparison");
    }
  }

  tos_value_ = type_system_["boolean"];
}

void TypeCheckingVisitor::Visit(ArithmeticalExpression* expression) {
  if (expression->lhs_) {
    int type_code = Accept(expression->lhs_);

    if (type_code != type_system_["int"]) {
      throw std::runtime_error("Non-int type in arithmetical expression");
    }
  }
  if (expression->rhs_) {
    int type_code = Accept(expression->rhs_);

    if (type_code != type_system_["int"]) {
      throw std::runtime_error("Non-int type in arithmetical expression");
    }
  }
  tos_value_ = type_system_["int"];
}

void TypeCheckingVisitor::Visit(ArrayAccessExpression* expression) {
  int type_code = Accept(expression->index_expression_);
  if (type_code != type_system_["int"]) {
    throw std::runtime_error("Non-int type expression in index");
  }

  NewScopeLayer* layer =
      current_layer_->GetArrayLayer(Symbol(expression->array_indent_));

  // -1 to get element type
  tos_value_ = layer->symbol_types_[Symbol(expression->array_indent_)] - 1;
}

////////////////////////////////////////////////////////////////////////////////

void TypeCheckingVisitor::Visit(MethodExpression* method_expression) {}

void TypeCheckingVisitor::Visit(Type* type) {}

void TypeCheckingVisitor::Visit(ArrayType* array_type) {}

////////////////////////////////////////////////////////////////////////////////

void TypeCheckingVisitor::PreVisit(Program* program) {
  type_system_["int"] = 1;
  type_system_["int[]"] = 2;
  type_system_["boolean"] = 3;
  type_system_["boolean[]"] = 4;

  program->class_declarations_->PreAccept(this);

  program->main_class_->PreAccept(this);
}

void TypeCheckingVisitor::PreVisit(MainClass* main_class) {}

void TypeCheckingVisitor::PreVisit(ClassDeclaration* class_declaration) {
  ++type_count_;
  type_system_[class_declaration->class_name_] = type_count_;

  ++type_count_;
  type_system_[class_declaration->class_name_ + "[]"] = type_count_;
}

void TypeCheckingVisitor::PreVisit(ListOfStatements* list_of_statements) {
  for (auto& statement : list_of_statements->list_of_statements_) {
    statement->PreAccept(this);
  }
}

void TypeCheckingVisitor::PreVisit(VariableDeclaration* variable_declaration) {}
void TypeCheckingVisitor::PreVisit(MethodDeclaration* method_declaration) {}
