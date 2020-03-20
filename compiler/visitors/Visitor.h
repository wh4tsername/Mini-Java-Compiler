#pragma once

#include "../declarations.h"

class Visitor {
 public:
  virtual void Visit(ArrayAccessExpression* expression) = 0;
  virtual void Visit(ArithmeticalExpression* expression) = 0;
  virtual void Visit(LogicalExpression* expression) = 0;
  virtual void Visit(LengthExpression* expression) = 0;
  virtual void Visit(NewArrayExpression* expression) = 0;
  virtual void Visit(NewVariableExpression* expression) = 0;
  virtual void Visit(NumeralExpression* expression) = 0;
  virtual void Visit(This* this_expression) = 0;
  virtual void Visit(VariableExpression* expression) = 0;
  virtual void Visit(MethodInvocation* method_invocation) = 0;
  virtual void Visit(VariableDeclaration* variable_declaration) = 0;
  virtual void Visit(MethodExpression* method_expression) = 0;
  virtual void Visit(Formals* formals) = 0;
  virtual void Visit(Lvalue* lvalue) = 0;
  virtual void Visit(Type* type) = 0;
  virtual void Visit(ArrayType* array_type) = 0;
  virtual void Visit(Program* program) = 0;
  virtual void Visit(ListOfStatements* list_of_statements) = 0;
  virtual void Visit(WhileStatement* statement) = 0;
  virtual void Visit(IfStatement* statement) = 0;
  virtual void Visit(ReturnStatement* statement) = 0;
  virtual void Visit(PrintStatement* statement) = 0;
  virtual void Visit(AssignmentStatement* statement) = 0;
  virtual void Visit(AssertStatement* statement) = 0;
  virtual void Visit(MethodDeclaration* method_declaration) = 0;
  virtual void Visit(MainClass* main_class) = 0;
  virtual void Visit(ClassDeclaration* class_declaration) = 0;
};
