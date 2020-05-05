#pragma once

#include <stdexcept>

#include "../../visitors/Node.h"
#include "../../visitors/Visitor.h"

class Statement : public Node {
 public:
  virtual void PreAccept(Visitor* visitor) {
    throw std::runtime_error("Wrong node PreAccepted!");
  }
};
