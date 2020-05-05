#include "NewSymbolTreeVisitor.h"

NewSymbolTreeVisitor::NewSymbolTreeVisitor() : tree_(new NewScopeLayer) {
  current_layer_ = tree_.root_;
}

NewScopeLayerTree& NewSymbolTreeVisitor::GetTree() { return tree_; }

////////////////////////////////////////////////////////////////////////////////

void NewSymbolTreeVisitor::Visit(Program* program) {
  PreVisit(program);

  if (program->class_declarations_) {
    program->class_declarations_->Accept(this);
  }

  program->main_class_->Accept(this);
}

void NewSymbolTreeVisitor::Visit(ListOfStatements* list_of_statements) {
  for (auto& statement : list_of_statements->list_of_statements_) {
    statement->Accept(this);
  }
}

void NewSymbolTreeVisitor::Visit(ClassDeclaration* class_declaration) {
  current_layer_->class_symbol_ = Symbol(class_declaration->class_name_);
  // PreVisiting checks if class is already declared
  // new scope
  current_layer_ =
      new NewScopeLayer(current_layer_, class_declaration->class_name_,
                        current_layer_->class_symbol_, Symbol());

  class_declaration->declarations_->Accept(this);

  current_layer_ = current_layer_->parent_;
}

void NewSymbolTreeVisitor::Visit(MainClass* main_class) {
  current_layer_->class_symbol_ = Symbol(main_class->main_class_name_);
  // PreVisiting checks if class is already declared
  // new scope
  current_layer_ =
      new NewScopeLayer(current_layer_, main_class->main_class_name_,
                        current_layer_->class_symbol_, Symbol());

  if (main_class->declarations_) {
    main_class->declarations_->Accept(this);
  }

  main_class->main_->Accept(this);

  current_layer_ = current_layer_->parent_;
}

void NewSymbolTreeVisitor::Visit(MethodDeclaration* method_declaration) {
  Symbol symbol(method_declaration->method_name_);

  // new scope
  current_layer_ = new NewScopeLayer(current_layer_, symbol.GetName(),
                                     current_layer_->class_symbol_,
                                     Symbol(method_declaration->method_name_));

  if (method_declaration->formals_) {
    method_declaration->formals_->Accept(this);
  }

  method_declaration->list_of_statements_->Accept(this);

  current_layer_ = current_layer_->parent_;
}

void NewSymbolTreeVisitor::Visit(Formals* formals) {
  for (auto& formal : formals->formals_) {
    current_layer_->DeclareVariable(formal.first, Symbol(formal.second));

    const std::string& type_name = formal.first->type_name_;

    if (type_name == "void") {
      throw std::runtime_error("Can't declare variable of void type");
    }

    // pre type checking to resolve class methods and fields
    if (type_name != "int" && type_name != "boolean" && type_name != "int[]" &&
        type_name != "boolean[]") {
      if (type_name.back() != ']') {
        current_layer_->user_type_system_[Symbol(formal.second)] = type_name;
      } else {
        std::string new_type_name;

        std::copy(type_name.begin(), type_name.end() - 2,
                  new_type_name.begin());

        current_layer_->user_type_system_[Symbol(formal.second)] =
            new_type_name;
      }
    }
  }
}

void NewSymbolTreeVisitor::Visit(
    ScopeListOfStatements* scope_list_of_statements) {
  current_layer_ = new NewScopeLayer(
      current_layer_, "new scope " + current_layer_->class_symbol_.GetName(),
      current_layer_->class_symbol_, current_layer_->method_symbol_);

  scope_list_of_statements->list_of_statements_->Accept(this);

  current_layer_ = current_layer_->parent_;
}

void NewSymbolTreeVisitor::Visit(PrintStatement* statement) {
  statement->expression_->Accept(this);
}

void NewSymbolTreeVisitor::Visit(AssertStatement* statement) {
  statement->expression_->Accept(this);
}

void NewSymbolTreeVisitor::Visit(ReturnStatement* statement) {
  statement->expression_->Accept(this);
}

void NewSymbolTreeVisitor::Visit(MethodExpression* method_expression) {
  for (auto& expression : method_expression->list_of_expressions_) {
    expression->Accept(this);
  }
}

void NewSymbolTreeVisitor::Visit(VariableDeclaration* variable_declaration) {
  current_layer_->DeclareVariable(variable_declaration->type_,
                                  Symbol(variable_declaration->variable_name_));

  const std::string& type_name = variable_declaration->type_->type_name_;

  if (type_name == "void") {
    throw std::runtime_error("Can't declare variable of void type");
  }

  // pre type checking to resolve class methods and fields
  if (type_name != "int" && type_name != "boolean" && type_name != "int[]" &&
      type_name != "boolean[]") {
    if (type_name.back() != ']') {
      current_layer_
          ->user_type_system_[Symbol(variable_declaration->variable_name_)] =
          type_name;
    } else {
      std::string new_type_name;

      std::copy(type_name.begin(), type_name.end() - 2, new_type_name.begin());

      current_layer_
          ->user_type_system_[Symbol(variable_declaration->variable_name_)] =
          new_type_name;
    }
  }
}

void NewSymbolTreeVisitor::Visit(VariableExpression* expression) {
  current_layer_->GetVariableLayer(Symbol(expression->variable_name_));
}

void NewSymbolTreeVisitor::Visit(NewArrayExpression* expression) {
  expression->length_->Accept(this);
}

void NewSymbolTreeVisitor::Visit(LengthExpression* expression) {
  current_layer_->GetVariableLayer(Symbol(expression->variable_name_));
}

void NewSymbolTreeVisitor::Visit(ArrayAccessExpression* expression) {
  current_layer_->GetArrayLayer(Symbol(expression->array_indent_));

  expression->index_expression_->Accept(this);
}

void NewSymbolTreeVisitor::Visit(ArithmeticalExpression* expression) {
  if (expression->lhs_) {
    expression->lhs_->Accept(this);
  }
  if (expression->rhs_) {
    expression->rhs_->Accept(this);
  }
}

void NewSymbolTreeVisitor::Visit(LogicalExpression* expression) {
  if (expression->lhs_) {
    expression->lhs_->Accept(this);
  }
  if (expression->rhs_) {
    expression->rhs_->Accept(this);
  }
}

////////////////////////////////////////////////////////////////////////////////

std::string NewSymbolTreeVisitor::UserTypeResolving(const Symbol& symbol) {
  NewScopeLayer* local_current = current_layer_;

  while (local_current->parent_ != nullptr &&
         local_current->user_type_system_.find(symbol) ==
             local_current->user_type_system_.end()) {
    local_current = local_current->parent_;
  }

  if (local_current->parent_ == nullptr) {
    throw std::runtime_error("Invalid method invocation from non user type");
  }

  return local_current->user_type_system_[symbol];
}

////////////////////////////////////////////////////////////////////////////////

void NewSymbolTreeVisitor::Visit(MethodInvocation* method_invocation) {
  Symbol class_name;
  if (method_invocation->call_from_ == "this") {
    class_name = current_layer_->class_symbol_;
  } else {
    const Symbol& symbol = Symbol(method_invocation->call_from_);

    current_layer_->GetVariableLayer(symbol);

    class_name = Symbol(UserTypeResolving(symbol));
  }

  if (std::get<1>(tree_.class_symbols_table_[class_name])
          .find(Symbol(method_invocation->method_name_)) ==
      std::get<1>(tree_.class_symbols_table_[class_name]).end()) {
    throw std::runtime_error("Can't find method name");
  }

  if (method_invocation->arguments_list_) {
    method_invocation->arguments_list_->Accept(this);
  }
}

void NewSymbolTreeVisitor::Visit(FieldAccess* field_access) {
  if (std::get<0>(tree_.class_symbols_table_[current_layer_->class_symbol_])
              .find(Symbol(field_access->field_name_)) ==
          std::get<0>(tree_.class_symbols_table_[current_layer_->class_symbol_])
              .end() &&
      std::get<2>(tree_.class_symbols_table_[current_layer_->class_symbol_])
              .find(Symbol(field_access->field_name_)) ==
          std::get<2>(tree_.class_symbols_table_[current_layer_->class_symbol_])
              .end()) {
    throw std::runtime_error("Invalid field access");
  }
}

void NewSymbolTreeVisitor::Visit(AssignmentStatement* statement) {
  statement->expression_->Accept(this);

  statement->lvalue_->Accept(this);
}

void NewSymbolTreeVisitor::Visit(Lvalue* lvalue) {
  if (lvalue->code_ == lvalue->VAR) {
    const Symbol& symbol = Symbol(lvalue->variable_name_);
    NewScopeLayer* current = current_layer_;

    while (!current->HasArray(symbol) && !current->HasVariable(symbol) &&
           current->parent_->parent_ != nullptr) {
      current = current->parent_;
    }

    if (current->parent_->parent_ == nullptr) {
      throw std::runtime_error("Variable or array " + symbol.GetName() +
                               " is not declared");
    }
  } else if (lvalue->code_ == lvalue->ARR) {
    lvalue->array_access_expression_->Accept(this);
  } else if (lvalue->code_ == lvalue->FIELD) {
    lvalue->field_access_->Accept(this);
  }
}

void NewSymbolTreeVisitor::Visit(WhileStatement* statement) {
  statement->expression_->Accept(this);
  statement->statement_->Accept(this);
}

void NewSymbolTreeVisitor::Visit(IfStatement* statement) {
  statement->expression_->Accept(this);
  statement->if_statement_->Accept(this);

  if (statement->else_statement_) {
    statement->else_statement_->Accept(this);
  }
}

////////////////////////////////////////////////////////////////////////////////

void NewSymbolTreeVisitor::Visit(Type* type) {}

void NewSymbolTreeVisitor::Visit(ArrayType* array_type) {}

void NewSymbolTreeVisitor::Visit(NumeralExpression* expression) {}

void NewSymbolTreeVisitor::Visit(NewVariableExpression* expression) {}

////////////////////////////////////////////////////////////////////////////////

void NewSymbolTreeVisitor::PreVisit(Program* program) {
  if (program->class_declarations_) {
    program->class_declarations_->PreAccept(this);
  }

  program->main_class_->PreAccept(this);
}

void NewSymbolTreeVisitor::PreVisit(MainClass* main_class) {
  current_layer_->class_symbol_ = Symbol(main_class->main_class_name_);
  if (tree_.class_symbols_table_.find(current_layer_->class_symbol_) !=
      tree_.class_symbols_table_.end()) {
    throw std::runtime_error("Main class " +
                             current_layer_->class_symbol_.GetName() +
                             " has been already declared!");
  }

  if (main_class->declarations_) {
    main_class->declarations_->PreAccept(this);
  }

  main_class->main_->PreAccept(this);
}

void NewSymbolTreeVisitor::PreVisit(ClassDeclaration* class_declaration) {
  current_layer_->class_symbol_ = Symbol(class_declaration->class_name_);
  if (tree_.class_symbols_table_.find(current_layer_->class_symbol_) !=
      tree_.class_symbols_table_.end()) {
    throw std::runtime_error("Class " +
                             current_layer_->class_symbol_.GetName() +
                             " has been already declared!");
  }

  class_declaration->declarations_->PreAccept(this);
}

void NewSymbolTreeVisitor::PreVisit(ListOfStatements* list_of_statements) {
  for (auto& statement : list_of_statements->list_of_statements_) {
    statement->PreAccept(this);
  }
}

void NewSymbolTreeVisitor::PreVisit(VariableDeclaration* variable_declaration) {
  Symbol symbol(variable_declaration->variable_name_);
  if (variable_declaration->type_->type_name_.back() != ']') {
    if (std::get<0>(tree_.class_symbols_table_[current_layer_->class_symbol_])
            .find(symbol) !=
        std::get<0>(tree_.class_symbols_table_[current_layer_->class_symbol_])
            .end()) {
      throw std::runtime_error(
          "In class " + current_layer_->class_symbol_.GetName() + " variable " +
          symbol.GetName() + " has been already declared!");
    }

    std::get<0>(
        tree_.class_symbols_table_[current_layer_->class_symbol_])[symbol] =
        std::make_pair(variable_declaration->type_->type_name_,
                       std::make_shared<UninitObject>());
  } else {
    if (std::get<2>(tree_.class_symbols_table_[current_layer_->class_symbol_])
            .find(symbol) !=
        std::get<2>(tree_.class_symbols_table_[current_layer_->class_symbol_])
            .end()) {
      throw std::runtime_error(
          "In class " + current_layer_->class_symbol_.GetName() + " array " +
          symbol.GetName() + " has been already declared!");
    }

    std::get<2>(
        tree_.class_symbols_table_[current_layer_->class_symbol_])[symbol] =
        std::make_pair(variable_declaration->type_->type_name_,
                       std::vector<std::shared_ptr<Object>>());
  }

  if (tree_.class_members_table_[current_layer_->class_symbol_].find(symbol) !=
      tree_.class_members_table_[current_layer_->class_symbol_].end()) {
    throw std::runtime_error("In class " +
                             current_layer_->class_symbol_.GetName() +
                             " member duplicate: " + symbol.GetName());
  }
  tree_.class_members_table_[current_layer_->class_symbol_].insert(symbol);
}

void NewSymbolTreeVisitor::PreVisit(MethodDeclaration* method_declaration) {
  Symbol symbol(method_declaration->method_name_);
  if (std::get<1>(tree_.class_symbols_table_[current_layer_->class_symbol_])
          .find(symbol) !=
      std::get<1>(tree_.class_symbols_table_[current_layer_->class_symbol_])
          .end()) {
    throw std::runtime_error(
        "In class " + current_layer_->class_symbol_.GetName() + " method " +
        symbol.GetName() + " has been already declared!");
  }

  size_t num_args = 0;
  if (method_declaration->formals_) {
    num_args = method_declaration->formals_->formals_.size();
  }

  std::vector<std::pair<std::string, std::string>> args(num_args);
  for (int i = 0; i < num_args; ++i) {
    args[i].first = method_declaration->formals_->formals_[i].first->type_name_;
    args[i].second = method_declaration->formals_->formals_[i].second;
  }

  std::get<1>(
      tree_.class_symbols_table_[current_layer_->class_symbol_])[symbol] =
      std::make_shared<Method>(std::move(args),
                               current_layer_->class_symbol_.GetName(),
                               method_declaration->type_->type_name_);

  if (tree_.class_members_table_[current_layer_->class_symbol_].find(symbol) !=
      tree_.class_members_table_[current_layer_->class_symbol_].end()) {
    throw std::runtime_error("In class " +
                             current_layer_->class_symbol_.GetName() +
                             " member duplicate: " + symbol.GetName());
  }
  tree_.class_members_table_[current_layer_->class_symbol_].insert(symbol);
}
