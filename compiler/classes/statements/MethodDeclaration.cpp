#include "MethodDeclaration.h"

MethodDeclaration::MethodDeclaration(std::string method_name, Type* type,
                                     Formals* formals,
                                     ListOfStatements* list_of_statements)
    : method_name_(std::move(method_name)),
      type_(type),
      formals_(formals),
      list_of_statements_(list_of_statements) {}

void MethodDeclaration::Accept(Visitor* visitor) { visitor->Visit(this); }

void MethodDeclaration::PreAccept(Visitor* visitor) {
  visitor->PreVisit(this);
}
