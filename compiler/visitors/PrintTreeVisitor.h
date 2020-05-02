#pragma once

#include "Visitor.h"
#include "../nodes.h"

#include <fstream>
#include <string>

class PrintTreeVisitor : public Visitor {
 public:
  explicit PrintTreeVisitor(const std::string& stream);
  ~PrintTreeVisitor();

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
  void PrintTabs();
  std::ofstream stream_;
  int number_of_tabs_ = 0;
};