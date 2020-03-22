#include "Executor.h"

Executor::Executor(ScopeLayer* root) : current_layer_(root) {
  offsets_.push(0);
  tos_value_ = 0;
}

void Executor::Exec() {}

void Executor::Visit(ArrayAccessExpression* expression) {}
void Executor::Visit(ArithmeticalExpression* expression) {}
void Executor::Visit(LogicalExpression* expression) {}
void Executor::Visit(LengthExpression* expression) {}
void Executor::Visit(NewArrayExpression* expression) {}
void Executor::Visit(NewVariableExpression* expression) {}
void Executor::Visit(NumeralExpression* expression) {}
void Executor::Visit(This* this_expression) {}
void Executor::Visit(VariableExpression* expression) {}
void Executor::Visit(MethodInvocation* method_invocation) {}
void Executor::Visit(VariableDeclaration* variable_declaration) {}
void Executor::Visit(MethodExpression* method_expression) {}
void Executor::Visit(Formals* formals) {}
void Executor::Visit(Lvalue* lvalue) {}
void Executor::Visit(Type* type) {}
void Executor::Visit(ArrayType* array_type) {}
void Executor::Visit(Program* program) {}
void Executor::Visit(ListOfStatements* list_of_statements) {}
void Executor::Visit(WhileStatement* statement) {}
void Executor::Visit(IfStatement* statement) {}
void Executor::Visit(ReturnStatement* statement) {}
void Executor::Visit(PrintStatement* statement) {}
void Executor::Visit(AssignmentStatement* statement) {}
void Executor::Visit(AssertStatement* statement) {}
void Executor::Visit(MethodDeclaration* method_declaration) {}
void Executor::Visit(MainClass* main_class) {}
void Executor::Visit(ClassDeclaration* class_declaration) {}
void Executor::Visit(ScopeListOfStatements* scope_list_of_statements) {}
