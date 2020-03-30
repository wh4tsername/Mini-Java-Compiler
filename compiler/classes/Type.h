#pragma once

#include <string>
#include "../visitors/Node.h"

class Type : public Node {
 public:
  explicit Type(std::string type_name);

  void Accept(Visitor* visitor) override;

  std::string type_name_;
};
