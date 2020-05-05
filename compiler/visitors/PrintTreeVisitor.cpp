#include "PrintTreeVisitor.h"

PrintTreeVisitor::PrintTreeVisitor(const std::string& filename)
    : stream_(filename) {}

PrintTreeVisitor::~PrintTreeVisitor() { stream_.close(); }

void PrintTreeVisitor::PrintTabs() {
  for (int i = 0; i < number_of_tabs_; ++i) {
    stream_ << '\t';
  }
}

void PrintTreeVisitor::Visit(ArrayAccessExpression* expression) {
  PrintTabs();
  stream_ << "Array access: " << std::endl;

  PrintTabs();
  stream_ << "(called from): " << expression->array_indent_ << std::endl;

  PrintTabs();
  stream_ << "(index): " << std::endl;
  ++number_of_tabs_;
  expression->index_expression_->Accept(this);
  --number_of_tabs_;
}

void PrintTreeVisitor::Visit(ArithmeticalExpression* expression) {
  PrintTabs();
  stream_ << "Arithmetical expression: "
          << "(operation): " << expression->operation_ << std::endl;

  ++number_of_tabs_;
  if (expression->lhs_) {
    expression->lhs_->Accept(this);
  }
  if (expression->rhs_) {
    expression->rhs_->Accept(this);
  }
  --number_of_tabs_;
}

void PrintTreeVisitor::Visit(LogicalExpression* expression) {
  PrintTabs();
  stream_ << "Logical expression: "
          << "(operation): " << expression->operation_ << std::endl;

  ++number_of_tabs_;
  if (expression->lhs_) {
    expression->lhs_->Accept(this);
  }
  if (expression->rhs_) {
    expression->rhs_->Accept(this);
  }
  --number_of_tabs_;
}

void PrintTreeVisitor::Visit(LengthExpression* expression) {
  PrintTabs();
  stream_ << "Length expression: "
          << "(called from): " << std::endl;

  ++number_of_tabs_;
  PrintTabs();
  stream_ << expression->variable_name_ << std::endl;
  --number_of_tabs_;
}

void PrintTreeVisitor::Visit(NewArrayExpression* expression) {
  PrintTabs();
  stream_ << "New array allocation: "
          << "(type): " << expression->type_name_->type_name_
          << " (length): " << std::endl;

  ++number_of_tabs_;
  expression->length_->Accept(this);
  --number_of_tabs_;
}

void PrintTreeVisitor::Visit(NewVariableExpression* expression) {
  PrintTabs();
  stream_ << "New var allocation: " << expression->variable_type_->type_name_
          << std::endl;
}

void PrintTreeVisitor::Visit(NumeralExpression* expression) {
  PrintTabs();
  stream_ << "Number: " << expression->value_ << std::endl;
}

void PrintTreeVisitor::Visit(VariableExpression* expression) {
  PrintTabs();
  stream_ << "Variable: " << expression->variable_name_ << std::endl;
}

void PrintTreeVisitor::Visit(MethodInvocation* method_invocation) {
  PrintTabs();
  stream_ << "Method invocation: " << method_invocation->method_name_
          << std::endl;

  if (method_invocation->arguments_list_ != nullptr) {
    PrintTabs();
    stream_ << "(arguments): " << std::endl;

    ++number_of_tabs_;
    for (auto&& argument :
         method_invocation->arguments_list_->list_of_expressions_) {
      argument->Accept(this);
    }
    --number_of_tabs_;
  } else {
    PrintTabs();
    stream_ << "no arguments" << std::endl;
  }

  PrintTabs();
  stream_ << "(called from): " << method_invocation->call_from_ << std::endl;
}

void PrintTreeVisitor::Visit(VariableDeclaration* variable_declaration) {
  PrintTabs();
  stream_ << "Variable declaration: " << variable_declaration->variable_name_
          << " -> " << variable_declaration->type_->type_name_ << std::endl;
}

void PrintTreeVisitor::Visit(MethodExpression* method_expression) {
  stream_ << "WTFFFFFFF" << std::endl;
}

void PrintTreeVisitor::Visit(Formals* formals) {
  stream_ << "WTFFFFFFF" << std::endl;
}

void PrintTreeVisitor::Visit(Lvalue* lvalue) {
  PrintTabs();
  stream_ << "Lvalue: " << std::endl;

  if (lvalue->code_ == Lvalue::CODE::ARR) {
    ++number_of_tabs_;
    lvalue->array_access_expression_->Accept(this);
    --number_of_tabs_;
  } else if (lvalue->code_ == Lvalue::CODE::VAR) {
    ++number_of_tabs_;
    PrintTabs();
    stream_ << lvalue->variable_name_ << std::endl;
    --number_of_tabs_;
  } else if (lvalue->code_ == Lvalue::CODE::FIELD) {
    ++number_of_tabs_;
    lvalue->field_access_->Accept(this);
    --number_of_tabs_;
  } else {
    throw std::runtime_error("Incorrect lvalue code!");
  }
}

void PrintTreeVisitor::Visit(Type* type) {
  stream_ << "WTFFFFFFF" << std::endl;
}

void PrintTreeVisitor::Visit(ArrayType* array_type) {
  stream_ << "WTFFFFFFF" << std::endl;
}

void PrintTreeVisitor::Visit(Program* program) {
  PrintTabs();
  stream_ << "Program: " << std::endl;

  ++number_of_tabs_;
  program->main_class_->Accept(this);
  program->class_declarations_->Accept(this);
  --number_of_tabs_;
}

void PrintTreeVisitor::Visit(ListOfStatements* list_of_statements) {
  if (!list_of_statements->list_of_statements_.empty()) {
    PrintTabs();
    stream_ << "Statements: " << std::endl;

    ++number_of_tabs_;
    for (auto&& statement : list_of_statements->list_of_statements_) {
      statement->Accept(this);
    }
    --number_of_tabs_;
  }
}

void PrintTreeVisitor::Visit(WhileStatement* statement) {
  PrintTabs();
  stream_ << "While: " << std::endl;

  ++number_of_tabs_;
  statement->expression_->Accept(this);
  statement->statement_->Accept(this);
  --number_of_tabs_;
}

void PrintTreeVisitor::Visit(IfStatement* statement) {
  PrintTabs();
  stream_ << "If statement: " << std::endl;

  PrintTabs();
  stream_ << "Expression: " << std::endl;
  ++number_of_tabs_;
  statement->expression_->Accept(this);
  --number_of_tabs_;

  PrintTabs();
  stream_ << "If: " << std::endl;
  ++number_of_tabs_;
  statement->if_statement_->Accept(this);
  --number_of_tabs_;

  if (statement->else_statement_) {
    PrintTabs();
    stream_ << "Else: " << std::endl;
    ++number_of_tabs_;
    statement->else_statement_->Accept(this);
    --number_of_tabs_;
  }
}

void PrintTreeVisitor::Visit(ReturnStatement* statement) {
  PrintTabs();
  stream_ << "Return: " << std::endl;

  ++number_of_tabs_;
  statement->expression_->Accept(this);
  --number_of_tabs_;
}

void PrintTreeVisitor::Visit(PrintStatement* statement) {
  PrintTabs();
  stream_ << "Print: " << std::endl;

  ++number_of_tabs_;
  statement->expression_->Accept(this);
  --number_of_tabs_;
}

void PrintTreeVisitor::Visit(AssignmentStatement* statement) {
  PrintTabs();
  stream_ << "Assignment: " << std::endl;

  ++number_of_tabs_;
  statement->lvalue_->Accept(this);
  statement->expression_->Accept(this);
  --number_of_tabs_;
}

void PrintTreeVisitor::Visit(AssertStatement* statement) {
  PrintTabs();
  stream_ << "Assert: " << std::endl;

  ++number_of_tabs_;
  statement->expression_->Accept(this);
  --number_of_tabs_;
}

void PrintTreeVisitor::Visit(MethodDeclaration* method_declaration) {
  PrintTabs();
  stream_ << "Method declaration: " << method_declaration->method_name_
          << ", (return type): " << method_declaration->type_->type_name_
          << ", (arguments): " << std::endl;

  if (method_declaration->formals_ != nullptr) {
    PrintTabs();
    for (auto&& formal : method_declaration->formals_->formals_) {
      stream_ << formal.second << " -> " << formal.first->type_name_;
      if (formal != method_declaration->formals_->formals_.back()) {
        stream_ << ", ";
      }
    }
    stream_ << std::endl;
  } else {
    PrintTabs();
    stream_ << "no arguments" << std::endl;
  }

  ++number_of_tabs_;
  method_declaration->list_of_statements_->Accept(this);
  --number_of_tabs_;
}

void PrintTreeVisitor::Visit(MainClass* main_class) {
  PrintTabs();
  stream_ << "Main class: " << main_class->main_class_name_ << std::endl;

  ++number_of_tabs_;

  PrintTabs();
  stream_ << "Main: " << std::endl;

  ++number_of_tabs_;
  main_class->main_->Accept(this);
  --number_of_tabs_;

  --number_of_tabs_;

  ++number_of_tabs_;
  main_class->declarations_->Accept(this);
  --number_of_tabs_;
}

void PrintTreeVisitor::Visit(ClassDeclaration* class_declaration) {
  PrintTabs();
  stream_ << "Class: " << class_declaration->class_name_ << std::endl;

  ++number_of_tabs_;
  class_declaration->declarations_->Accept(this);
  --number_of_tabs_;
}

void PrintTreeVisitor::Visit(ScopeListOfStatements* scope_list_of_statements) {
  PrintTabs();
  stream_ << "[new scope]" << std::endl;

  scope_list_of_statements->list_of_statements_->Accept(this);
}

void PrintTreeVisitor::Visit(FieldAccess* field_access) {
  PrintTabs();
  stream_ << "FieldAccess: " << std::endl;

  PrintTabs();
  stream_ << field_access->field_name_ << std::endl;
}

void PrintTreeVisitor::PreVisit(Program* program) {}
void PrintTreeVisitor::PreVisit(MainClass* main_class) {}
void PrintTreeVisitor::PreVisit(ClassDeclaration* class_declaration) {}
void PrintTreeVisitor::PreVisit(ListOfStatements* list_of_statements) {}
void PrintTreeVisitor::PreVisit(VariableDeclaration* variable_declaration) {}
void PrintTreeVisitor::PreVisit(MethodDeclaration* method_declaration) {}
