#include "TemplateVisitor.h"
#include "../IR/wrappers/SubtreeWrapper.h"
#include "../objects/values/Value.h"

template <typename T>
T TemplateVisitor<T>::Accept(Node* node) {
  node->Accept(this);
  return tos_value_;
}

template int TemplateVisitor<int>::Accept(Node* node);
template Value* TemplateVisitor<Value*>::Accept(Node* node);
template IRT::SubtreeWrapper* TemplateVisitor<IRT::SubtreeWrapper*>::Accept(
    Node* node);
