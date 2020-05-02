#include "SymbolTreeVisitor.h"

SymbolTreeVisitor::SymbolTreeVisitor() : tree_(new ScopeLayer) {
  current_layer_ = tree_.root_;
}

ScopeLayerTree SymbolTreeVisitor::GetRoot() { return tree_; }

std::unordered_map<Symbol, MethodDeclaration*>
SymbolTreeVisitor::GetFunctions() {
  return functions_;
}

void SymbolTreeVisitor::Visit(ArrayAccessExpression* expression) {
  current_layer_->Get(Symbol(expression->array_indent_));

  expression->index_expression_->Accept(this);
}

void SymbolTreeVisitor::Visit(ArithmeticalExpression* expression) {
  if (expression->lhs_) {
    expression->lhs_->Accept(this);
  }
  expression->rhs_->Accept(this);
}

void SymbolTreeVisitor::Visit(LogicalExpression* expression) {
  if (expression->lhs_) {
    expression->lhs_->Accept(this);
  }
  if (expression->rhs_) {
    expression->rhs_->Accept(this);
  }
}

void SymbolTreeVisitor::Visit(LengthExpression* expression) {
  current_layer_->Get(Symbol(expression->variable_name_));
}

void SymbolTreeVisitor::Visit(NewArrayExpression* expression) {
  expression->length_->Accept(this);
}

void SymbolTreeVisitor::Visit(NewVariableExpression* expression) {}

void SymbolTreeVisitor::Visit(NumeralExpression* expression) {}

void SymbolTreeVisitor::Visit(This* this_expression) {}

void SymbolTreeVisitor::Visit(VariableExpression* expression) {
  current_layer_->Get(Symbol(expression->variable_name_));
}

void SymbolTreeVisitor::Visit(MethodInvocation* method_invocation) {
  method_invocation->call_from_->Accept(this);

  if (method_invocation->arguments_list_ != nullptr) {
    method_invocation->arguments_list_->Accept(this);
  }
}

void SymbolTreeVisitor::Visit(VariableDeclaration* variable_declaration) {
  current_layer_->DeclareVariable(Symbol(variable_declaration->variable_name_));
}

void SymbolTreeVisitor::Visit(MethodExpression* method_expression) {
  for (auto& expression : method_expression->list_of_expressions_) {
    expression->Accept(this);
  }
}

void SymbolTreeVisitor::Visit(Formals* formals) {
  for (const auto& formal : formals->formals_) {
    current_layer_->DeclareVariable(Symbol(formal.second));
  }
}

void SymbolTreeVisitor::Visit(Lvalue* lvalue) {
  if (lvalue->is_array_) {
    lvalue->array_access_expression_->Accept(this);
  } else {
    current_layer_->Get(Symbol(lvalue->variable_name_));
  }
}

void SymbolTreeVisitor::Visit(Type* type) {}

void SymbolTreeVisitor::Visit(ArrayType* array_type) {}

void SymbolTreeVisitor::Visit(Program* program) {
  // @TODO classes and scopes
  if (program->class_declarations_ != nullptr) {
    program->class_declarations_->Accept(this);
  }

  program->main_class_->Accept(this);
}

void SymbolTreeVisitor::Visit(ListOfStatements* list_of_statements) {
  for (auto& statement : list_of_statements->list_of_statements_) {
    statement->Accept(this);
  }
}

void SymbolTreeVisitor::Visit(WhileStatement* statement) {
  statement->expression_->Accept(this);
  statement->statement_->Accept(this);
}

void SymbolTreeVisitor::Visit(IfStatement* statement) {
  statement->expression_->Accept(this);
  statement->if_statement_->Accept(this);
  statement->if_statement_->Accept(this);
}

void SymbolTreeVisitor::Visit(ReturnStatement* statement) {
  statement->expression_->Accept(this);
}

void SymbolTreeVisitor::Visit(PrintStatement* statement) {
  statement->expression_->Accept(this);
}

void SymbolTreeVisitor::Visit(AssignmentStatement* statement) {
  statement->lvalue_->Accept(this);
  statement->expression_->Accept(this);
}

void SymbolTreeVisitor::Visit(AssertStatement* statement) {
  statement->expression_->Accept(this);
}

void SymbolTreeVisitor::Visit(MethodDeclaration* method_declaration) {
  current_layer_->DeclareFunction(Symbol(method_declaration->method_name_),
                                  method_declaration);

  auto new_layer = new ScopeLayer(current_layer_);

  current_layer_ = new_layer;

  if (method_declaration->formals_ != nullptr) {
    method_declaration->formals_->Accept(this);
  }

  method_declaration->list_of_statements_->Accept(this);

  tree_.AddMapping(Symbol(method_declaration->method_name_), new_layer);

  current_layer_ = current_layer_->GetParent();

  functions_[Symbol(method_declaration->method_name_)] = method_declaration;
}

void SymbolTreeVisitor::Visit(MainClass* main_class) {
  // @TODO class decl

  main_class->declarations_->Accept(this);
  main_class->main_->Accept(this);
}

void SymbolTreeVisitor::Visit(ClassDeclaration* class_declaration) {
  // @TODO single class for now
  class_declaration->declarations_->Accept(this);
}

void SymbolTreeVisitor::Visit(ScopeListOfStatements* scope_list_of_statements) {
  auto new_layer = new ScopeLayer(current_layer_);

  current_layer_ = new_layer;
  scope_list_of_statements->list_of_statements_->Accept(this);
  current_layer_ = current_layer_->GetParent();
}
