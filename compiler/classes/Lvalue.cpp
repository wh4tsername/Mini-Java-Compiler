#include "Lvalue.h"

#include <utility>

Lvalue::Lvalue(std::string variable_name,
               ArrayAccessExpression* array_access_expression, bool is_array)
    : variable_name_(std::move(variable_name)),
      array_access_expression_(array_access_expression),
      is_array_(is_array) {}

void Lvalue::Accept(Visitor* visitor) { visitor->Visit(this); }
