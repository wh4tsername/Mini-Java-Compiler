#pragma once

#include <stack>
#include <cassert>

#include "../function_processing/FrameEmulator.h"
#include "../function_processing/FunctionTable.h"
#include "../function_processing/FunctionStorage.h"
#include "../objects/Function.h"
#include "../symbol_table/ScopeLayer.h"
#include "../symbol_table/ScopeLayerTree.h"
#include "TemplateVisitor.h"

class FunctionProcessingVisitor : public TemplateVisitor<int> {
 public:
  explicit FunctionProcessingVisitor(ScopeLayer* function_scope,
                                     std::shared_ptr<Function> function);

  void SetTree(ScopeLayerTree* tree);
  void SetParams(const std::vector<int>& params);
  FrameEmulator& GetFrame();

  void Visit(ArrayAccessExpression* expression) override;
  void Visit(ArithmeticalExpression* expression) override;
  void Visit(LogicalExpression* expression) override;
  void Visit(LengthExpression* expression) override;
  void Visit(NewArrayExpression* expression) override;
  void Visit(NewVariableExpression* expression) override;
  void Visit(NumeralExpression* expression) override;
  void Visit(This* this_expression) override;
  void Visit(VariableExpression* expression) override;
  void Visit(MethodInvocation* method_invocation) override;
  void Visit(VariableDeclaration* variable_declaration) override;
  void Visit(MethodExpression* method_expression) override;
  void Visit(Formals* formals) override;
  void Visit(Lvalue* lvalue) override;
  void Visit(Type* type) override;
  void Visit(ArrayType* array_type) override;
  void Visit(Program* program) override;
  void Visit(ListOfStatements* list_of_statements) override;
  void Visit(WhileStatement* statement) override;
  void Visit(IfStatement* statement) override;
  void Visit(ReturnStatement* statement) override;
  void Visit(PrintStatement* statement) override;
  void Visit(AssignmentStatement* statement) override;
  void Visit(AssertStatement* statement) override;
  void Visit(MethodDeclaration* method_declaration) override;
  void Visit(MainClass* main_class) override;
  void Visit(ClassDeclaration* class_declaration) override;
  void Visit(ScopeListOfStatements* scope_list_of_statements) override;

 private:
  ScopeLayer* root_layer_;
  ScopeLayer* current_layer_;
  std::stack<int> offsets_;
  FrameEmulator frame_;
  FunctionTable table_;
  ScopeLayerTree* tree_;
  bool returned_ = false;
};
