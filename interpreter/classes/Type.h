#pragma once

#include <string>
#include "../visitors/Node.h"

class Type : public Node {
 public:
  explicit Type(std::string type_name);

  std::string GetType();

  void Accept(Visitor* visitor) override;

 private:
  std::string type_name_;
};
