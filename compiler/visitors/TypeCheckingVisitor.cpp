#include "TypeCheckingVisitor.h"

void TypeCheckingVisitor::Visit(Program* program) {
  program->main_class_->Accept(this);
  program->class_declarations_->Accept(this);
}



////////////////////////////////////////////////////////////////////////////////

void TypeCheckingVisitor::PreVisit(Program* program) {}
void TypeCheckingVisitor::PreVisit(MainClass* main_class) {}
void TypeCheckingVisitor::PreVisit(ClassDeclaration* class_declaration) {}
void TypeCheckingVisitor::PreVisit(ListOfStatements* list_of_statements) {}
void TypeCheckingVisitor::PreVisit(VariableDeclaration* variable_declaration) {}
void TypeCheckingVisitor::PreVisit(MethodDeclaration* method_declaration) {}
