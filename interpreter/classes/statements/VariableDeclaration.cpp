#include "VariableDeclaration.h"

VariableDeclaration::VariableDeclaration(Type* type, std::string variable_name)
    : type_(type), variable_name_(std::move(variable_name)) {}

int VariableDeclaration::Count() { return 0; }

void VariableDeclaration::Run() {}
