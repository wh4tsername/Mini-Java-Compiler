#include "ClassDeclaration.h"

ClassDeclaration::ClassDeclaration(std::string class_name,
                                   ListOfStatements* declarations)
    : class_name_(std::move(class_name)), declarations_(declarations) {}

void ClassDeclaration::Accept(Visitor* visitor) {
  visitor->Visit(this);
}

void ClassDeclaration::PreAccept(Visitor* visitor) {
  visitor->PreVisit(this);
}
