#include "TemplateVisitor.h"

template<typename T>
T TemplateVisitor<T>::Accept(Node* node) {
  node->Accept(this);
  return tos_value_;
}

template int TemplateVisitor<int>::Accept(Node* node);
