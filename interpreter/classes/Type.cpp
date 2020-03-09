#include "Type.h"

Type::Type(std::string type_name) : type_name_(std::move(type_name)) {}

std::string Type::GetType() { return type_name_; }
