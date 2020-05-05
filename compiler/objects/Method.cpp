#include "Method.h"

Method::Method(const std::vector<std::pair<std::string, std::string>>& args,
               std::string owner_class, std::string return_type)
    : owner_class_(std::move(owner_class)),
      return_type_(std::move(return_type)) {
  for (const auto& pair : args) {
    arguments_.emplace_back(new Integer(0));
    types_.emplace_back(pair.first);
    argument_names_.emplace_back(pair.second);
  }
}
