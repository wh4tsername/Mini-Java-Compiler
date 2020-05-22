#include "NewFunctionProcessingVisitor.h"

NewFunctionProcessingVisitor::NewFunctionProcessingVisitor(
    NewScopeLayerTree* tree, NewScopeLayer* main_layer,
    std::shared_ptr<Method>&& main_func_ptr)
    : tree_(tree),
      root_layer_(main_layer),
      frame_(std::move(main_func_ptr)),
      is_returned_(false) {
  tree_->root_->PrepareTraversing();

  current_layer_ = root_layer_;
  tos_value_ = 0;
  offsets_.push(0);
}

////////////////////////////////////////////////////////////////////////////////

// void NewFunctionProcessingVisitor::Visit(Program* program) {}
//
// void NewFunctionProcessingVisitor::Visit(ListOfStatements*
// list_of_statements) {
//  for (auto&& statement : list_of_statements->list_of_statements_) {
//    if (!is_returned_) {
//      statement->Accept(this);
//    }
//  }
//}

////////////////////////////////////////////////////////////////////////////////

void NewFunctionProcessingVisitor::Visit(ArrayAccessExpression* expression) {}
void NewFunctionProcessingVisitor::Visit(ArithmeticalExpression* expression) {}
void NewFunctionProcessingVisitor::Visit(LogicalExpression* expression) {}
void NewFunctionProcessingVisitor::Visit(LengthExpression* expression) {}
void NewFunctionProcessingVisitor::Visit(NewArrayExpression* expression) {}
void NewFunctionProcessingVisitor::Visit(NewVariableExpression* expression) {}
void NewFunctionProcessingVisitor::Visit(NumeralExpression* expression) {}
void NewFunctionProcessingVisitor::Visit(VariableExpression* expression) {}
void NewFunctionProcessingVisitor::Visit(MethodInvocation* method_invocation) {}
void NewFunctionProcessingVisitor::Visit(FieldAccess* field_access) {}
void NewFunctionProcessingVisitor::Visit(
    VariableDeclaration* variable_declaration) {}
void NewFunctionProcessingVisitor::Visit(MethodExpression* method_expression) {}
void NewFunctionProcessingVisitor::Visit(Formals* formals) {}
void NewFunctionProcessingVisitor::Visit(Lvalue* lvalue) {}
void NewFunctionProcessingVisitor::Visit(Type* type) {}
void NewFunctionProcessingVisitor::Visit(ArrayType* array_type) {}
void NewFunctionProcessingVisitor::Visit(Program* program) {}
void NewFunctionProcessingVisitor::Visit(ListOfStatements* list_of_statements) {
}
void NewFunctionProcessingVisitor::Visit(WhileStatement* statement) {}
void NewFunctionProcessingVisitor::Visit(IfStatement* statement) {}
void NewFunctionProcessingVisitor::Visit(ReturnStatement* statement) {}
void NewFunctionProcessingVisitor::Visit(PrintStatement* statement) {}
void NewFunctionProcessingVisitor::Visit(AssignmentStatement* statement) {}
void NewFunctionProcessingVisitor::Visit(AssertStatement* statement) {}
void NewFunctionProcessingVisitor::Visit(
    MethodDeclaration* method_declaration) {}
void NewFunctionProcessingVisitor::Visit(MainClass* main_class) {}
void NewFunctionProcessingVisitor::Visit(ClassDeclaration* class_declaration) {}
void NewFunctionProcessingVisitor::Visit(
    ScopeListOfStatements* scope_list_of_statements) {}

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
