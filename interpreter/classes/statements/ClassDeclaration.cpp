#include "ClassDeclaration.h"

ClassDeclaration::ClassDeclaration(std::string class_name,
                                   ListOfStatements* declarations)
    : class_name_(std::move(class_name)), declarations_(declarations) {}

void ClassDeclaration::Run() {}
