#include "MethodDeclaration.h"

MethodDeclaration::MethodDeclaration(Type* type, Formals* formals,
                                     ListOfStatements* list_of_statements)
    : type_(type), formals_(formals), list_of_statements_(list_of_statements) {}

void MethodDeclaration::Run() {}

void MethodDeclaration::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
