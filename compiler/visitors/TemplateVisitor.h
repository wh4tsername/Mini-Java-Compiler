#pragma once

#include "Visitor.h"
#include "../nodes.h"
#include "Node.h"

template<typename T>
class TemplateVisitor : public Visitor {
 public:
  T Accept(Node* node);
 protected:
  T tos_value_;
};
