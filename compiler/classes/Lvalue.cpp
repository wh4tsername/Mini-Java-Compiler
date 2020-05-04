#include "Lvalue.h"

#include <utility>

Lvalue::Lvalue(std::string variable_name,
               ArrayAccessExpression* array_access_expression,
               FieldAccess* field_access, int code)
    : variable_name_(std::move(variable_name)),
      array_access_expression_(array_access_expression),
      field_access_(field_access),
      code_(code) {}

void Lvalue::Accept(Visitor* visitor) { visitor->Visit(this); }
