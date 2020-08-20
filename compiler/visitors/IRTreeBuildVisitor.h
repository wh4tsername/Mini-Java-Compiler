#pragma once

#include <stack>

#include "../IR/nodes/statements/Statement.h"
#include "../IR/wrappers/SubtreeWrapper.h"
#include "../function_processing/FrameTranslator.h"
#include "../symbol_table/NewScopeLayer.h"
#include "../symbol_table/NewScopeLayerTree.h"
#include "TemplateVisitor.h"

using IrtMapping = std::unordered_map<std::string, IRT::Statement*>;

class IRTreeBuildVisitor : public TemplateVisitor<IRT::SubtreeWrapper*> {
 public:
  explicit IRTreeBuildVisitor(NewScopeLayerTree* tree);

  void TraverseToChildByIndex();
  IrtMapping GetTrees();
  NewScopeLayer* GetCurrentLayer() const;
  std::string GetCurrentClassName() const;

  std::string TypeResolving(const Symbol& symbol) const;

  void Visit(ArrayAccessExpression* expression) override;
  void Visit(ArithmeticalExpression* expression) override;
  void Visit(LogicalExpression* expression) override;
  void Visit(LengthExpression* expression) override;
  void Visit(NewArrayExpression* expression) override;
  void Visit(NewVariableExpression* expression) override;
  void Visit(NumeralExpression* expression) override;
  void Visit(VariableExpression* expression) override;
  void Visit(MethodInvocation* method_invocation) override;
  void Visit(FieldAccess* field_access) override;
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

  void PreVisit(Program* program) override;
  void PreVisit(MainClass* main_class) override;
  void PreVisit(ClassDeclaration* class_declaration) override;
  void PreVisit(ListOfStatements* list_of_statements) override;
  void PreVisit(VariableDeclaration* variable_declaration) override;
  void PreVisit(MethodDeclaration* method_declaration) override;

 private:
  std::string current_classname_;

  NewScopeLayerTree* tree_;
  NewScopeLayer* current_layer_;

  std::stack<int> offsets_;
  std::unordered_map<std::string, IRT::FrameTranslator*> frame_translator_;
  IRT::FrameTranslator* current_frame_;

  IrtMapping method_trees_;
};
