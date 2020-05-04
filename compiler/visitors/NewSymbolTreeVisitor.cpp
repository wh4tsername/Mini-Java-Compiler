#include "NewSymbolTreeVisitor.h"

// TODO return value type

NewSymbolTreeVisitor::NewSymbolTreeVisitor() : tree_(new NewScopeLayer) {
  current_layer_ = tree_.root_;
}

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
  class_symbol_ = Symbol(class_declaration->class_name_);
  // check if class decl and decl it
  if (classes_.find(Symbol(class_declaration->class_name_)) != classes_.end()) {
    throw std::runtime_error("Class has been already declared!");
  }
  classes_[Symbol(class_declaration->class_name_)] = class_declaration;

  // new scope
  current_layer_ =
      new NewScopeLayer(current_layer_, class_declaration->class_name_);

  class_declaration->declarations_->Accept(this);

  current_layer_ = current_layer_->parent_;
}

void NewSymbolTreeVisitor::Visit(MainClass* main_class) {
  class_symbol_ = Symbol(main_class->main_class_name_);
  // check if class decl and decl it
  if (classes_.find(Symbol(main_class->main_class_name_)) != classes_.end()) {
    throw std::runtime_error("Main class has been already declared!");
  }
  main_class_ = main_class;

  // new scope
  current_layer_ =
      new NewScopeLayer(current_layer_, main_class->main_class_name_);

  main_class->declarations_->Accept(this);

  main_class->main_->Accept(this);

  current_layer_ = current_layer_->parent_;
}

void NewSymbolTreeVisitor::Visit(MethodDeclaration* method_declaration) {
  Symbol symbol(method_declaration->method_name_);
  // check
  if (std::get<1>(tree_.class_symbols_table_[class_symbol_]).find(symbol) !=
      std::get<1>(tree_.class_symbols_table_[class_symbol_]).end()) {
    throw std::runtime_error("In class " + class_symbol_.GetName() +
                             " variable " + symbol.GetName() +
                             " has been already declared!");
  }

  // new scope
  current_layer_ = new NewScopeLayer(current_layer_, symbol.GetName());

  if (method_declaration->formals_ != nullptr) {
    method_declaration->formals_->Accept(this);
  }

  method_declaration->list_of_statements_->Accept(this);

  current_layer_ = current_layer_->parent_;
}

void NewSymbolTreeVisitor::Visit(Formals* formals) {
  for (auto& formal : formals->formals_) {
    current_layer_->DeclareVariable(formal.first, Symbol(formal.second));
  }
}

void NewSymbolTreeVisitor::Visit(
    ScopeListOfStatements* scope_list_of_statements) {
  current_layer_ =
      new NewScopeLayer(current_layer_, "new scope " + class_symbol_.GetName());

  scope_list_of_statements->list_of_statements_->Accept(this);

  current_layer_ = current_layer_->parent_;
}

////////////////////////////////////////////////////////////////////////////////

void NewSymbolTreeVisitor::Visit(Type* type) {}

void NewSymbolTreeVisitor::Visit(ArrayType* array_type) {}

////////////////////////////////////////////////////////////////////////////////

void NewSymbolTreeVisitor::PreVisit(Program* program) {
  if (program->class_declarations_) {
    program->class_declarations_->PreAccept(this);
  }

  program->main_class_->PreAccept(this);
}

void NewSymbolTreeVisitor::PreVisit(MainClass* main_class) {
  class_symbol_ = Symbol(main_class->main_class_name_);
  if (tree_.class_symbols_table_.find(class_symbol_) !=
      tree_.class_symbols_table_.end()) {
    throw std::runtime_error("Main class " + class_symbol_.GetName() +
                             " has been already declared!");
  }

  if (main_class->declarations_) {
    main_class->declarations_->PreAccept(this);
  }

  main_class->main_->PreAccept(this);
}

void NewSymbolTreeVisitor::PreVisit(ClassDeclaration* class_declaration) {
  class_symbol_ = Symbol(class_declaration->class_name_);
  if (tree_.class_symbols_table_.find(class_symbol_) !=
      tree_.class_symbols_table_.end()) {
    throw std::runtime_error("Class " + class_symbol_.GetName() +
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
    if (std::get<0>(tree_.class_symbols_table_[class_symbol_]).find(symbol) !=
        std::get<0>(tree_.class_symbols_table_[class_symbol_]).end()) {
      throw std::runtime_error("In class " + class_symbol_.GetName() +
                               " variable " + symbol.GetName() +
                               " has been already declared!");
    }

    std::get<0>(tree_.class_symbols_table_[class_symbol_])[symbol] =
        std::make_shared<UninitObject>();
  } else {
    if (std::get<2>(tree_.class_symbols_table_[class_symbol_]).find(symbol) !=
        std::get<2>(tree_.class_symbols_table_[class_symbol_]).end()) {
      throw std::runtime_error("In class " + class_symbol_.GetName() +
                               " array " + symbol.GetName() +
                               " has been already declared!");
    }

    std::get<2>(tree_.class_symbols_table_[class_symbol_])[symbol] =
        std::vector<std::shared_ptr<Object>>();
  }
}

void NewSymbolTreeVisitor::PreVisit(MethodDeclaration* method_declaration) {
  Symbol symbol(method_declaration->method_name_);
  if (std::get<1>(tree_.class_symbols_table_[class_symbol_]).find(symbol) !=
      std::get<1>(tree_.class_symbols_table_[class_symbol_]).end()) {
    throw std::runtime_error("In class " + class_symbol_.GetName() +
                             " method " + symbol.GetName() +
                             " has been already declared!");
  }

  size_t num_args = method_declaration->formals_->formals_.size();
  std::vector<std::string> args(num_args);
  for (int i = 0; i < num_args; ++i) {
    args[i] = method_declaration->formals_->formals_[i].second;
  }

  std::get<1>(tree_.class_symbols_table_[class_symbol_])[symbol] =
      std::make_shared<Method>(std::move(args), class_symbol_.GetName());
}
