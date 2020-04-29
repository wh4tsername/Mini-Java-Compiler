#include "FunctionProcessingVisitor.h"

FunctionProcessingVisitor::FunctionProcessingVisitor(
    ScopeLayer* function_scope, std::shared_ptr<Function> function)
    : root_layer_(function_scope), frame_(std::move(function)), tree_(nullptr) {
  current_layer_ = root_layer_;
  offsets_.push(0);
  tos_value_ = 0;
}

void FunctionProcessingVisitor::SetTree(ScopeLayerTree* tree) { tree_ = tree; }

Frame& FunctionProcessingVisitor::GetFrame() { return frame_; }

void FunctionProcessingVisitor::Visit(ArrayAccessExpression* expression) {}
void FunctionProcessingVisitor::Visit(ArithmeticalExpression* expression) {}
void FunctionProcessingVisitor::Visit(LogicalExpression* expression) {}
void FunctionProcessingVisitor::Visit(LengthExpression* expression) {}
void FunctionProcessingVisitor::Visit(NewArrayExpression* expression) {}
void FunctionProcessingVisitor::Visit(NewVariableExpression* expression) {}
void FunctionProcessingVisitor::Visit(NumeralExpression* expression) {}
void FunctionProcessingVisitor::Visit(This* this_expression) {}
void FunctionProcessingVisitor::Visit(VariableExpression* expression) {}
void FunctionProcessingVisitor::Visit(MethodInvocation* method_invocation) {}
void FunctionProcessingVisitor::Visit(
    VariableDeclaration* variable_declaration) {}
void FunctionProcessingVisitor::Visit(MethodExpression* method_expression) {}
void FunctionProcessingVisitor::Visit(Formals* formals) {}
void FunctionProcessingVisitor::Visit(Lvalue* lvalue) {}
void FunctionProcessingVisitor::Visit(Type* type) {}
void FunctionProcessingVisitor::Visit(ArrayType* array_type) {}
void FunctionProcessingVisitor::Visit(Program* program) {}
void FunctionProcessingVisitor::Visit(ListOfStatements* list_of_statements) {}
void FunctionProcessingVisitor::Visit(WhileStatement* statement) {}
void FunctionProcessingVisitor::Visit(IfStatement* statement) {}
void FunctionProcessingVisitor::Visit(ReturnStatement* statement) {}
void FunctionProcessingVisitor::Visit(PrintStatement* statement) {}
void FunctionProcessingVisitor::Visit(AssignmentStatement* statement) {}
void FunctionProcessingVisitor::Visit(AssertStatement* statement) {}
void FunctionProcessingVisitor::Visit(MethodDeclaration* method_declaration) {}
void FunctionProcessingVisitor::Visit(MainClass* main_class) {}
void FunctionProcessingVisitor::Visit(ClassDeclaration* class_declaration) {}
void FunctionProcessingVisitor::Visit(
    ScopeListOfStatements* scope_list_of_statements) {}
