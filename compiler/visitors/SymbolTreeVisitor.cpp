#include "SymbolTreeVisitor.h"

SymbolTreeVisitor::SymbolTreeVisitor() : tree_(new ScopeLayer) {
  current_layer_ = tree_.GetRoot();
}

ScopeLayer* SymbolTreeVisitor::GetRoot() { return current_layer_; }

void SymbolTreeVisitor::Visit(ArrayAccessExpression* expression) {}
void SymbolTreeVisitor::Visit(ArithmeticalExpression* expression) {}
void SymbolTreeVisitor::Visit(LogicalExpression* expression) {}
void SymbolTreeVisitor::Visit(LengthExpression* expression) {}
void SymbolTreeVisitor::Visit(NewArrayExpression* expression) {}
void SymbolTreeVisitor::Visit(NewVariableExpression* expression) {}
void SymbolTreeVisitor::Visit(NumeralExpression* expression) {}
void SymbolTreeVisitor::Visit(This* this_expression) {}
void SymbolTreeVisitor::Visit(VariableExpression* expression) {}
void SymbolTreeVisitor::Visit(MethodInvocation* method_invocation) {}
void SymbolTreeVisitor::Visit(VariableDeclaration* variable_declaration) {}
void SymbolTreeVisitor::Visit(MethodExpression* method_expression) {}
void SymbolTreeVisitor::Visit(Formals* formals) {}
void SymbolTreeVisitor::Visit(Lvalue* lvalue) {}
void SymbolTreeVisitor::Visit(Type* type) {}
void SymbolTreeVisitor::Visit(ArrayType* array_type) {}
void SymbolTreeVisitor::Visit(Program* program) {}
void SymbolTreeVisitor::Visit(ListOfStatements* list_of_statements) {}
void SymbolTreeVisitor::Visit(WhileStatement* statement) {}
void SymbolTreeVisitor::Visit(IfStatement* statement) {}
void SymbolTreeVisitor::Visit(ReturnStatement* statement) {}
void SymbolTreeVisitor::Visit(PrintStatement* statement) {}
void SymbolTreeVisitor::Visit(AssignmentStatement* statement) {}
void SymbolTreeVisitor::Visit(AssertStatement* statement) {}
void SymbolTreeVisitor::Visit(MethodDeclaration* method_declaration) {}
void SymbolTreeVisitor::Visit(MainClass* main_class) {}
void SymbolTreeVisitor::Visit(ClassDeclaration* class_declaration) {}
void SymbolTreeVisitor::Visit(ScopeListOfStatements* scope_list_of_statements) {
}
