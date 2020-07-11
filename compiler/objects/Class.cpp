#include "Class.h"

Class::Class(ClassDeclaration* class_declaration)
    : class_declaration_(class_declaration) {}

void Class::AddMethod(const Symbol& symbol, std::shared_ptr<Method> method) {
  method_symbols_.emplace_back(symbol);
  method_objects_[symbol] = std::move(method);
}

void Class::AddField(const Symbol& symbol,
                     std::shared_ptr<PrimitiveObject> field) {
  field_symbols_.emplace_back(symbol);
  field_objects_[symbol] = std::move(field);
}

std::string Class::GetTypename() { return "Class"; }
