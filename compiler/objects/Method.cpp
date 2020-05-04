#include "Method.h"

Method::Method(const std::vector<std::string>& argument_names,
               std::string owner_class)
    : argument_names_(argument_names), owner_class_(std::move(owner_class)) {
  for (const std::string& name : argument_names) {
    arguments_.push_back(new Integer(0));
  }
}
