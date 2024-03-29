#include "TemplateVisitor.h"
#include "IRTStorage.h"
#include "../generators/Temporary.h"

using namespace IRT;

template <typename T>
T TemplateVisitor<T>::Accept(BaseElement* base_element) {
  base_element->Accept(this);
  return tos_value_;
}

template int TemplateVisitor<int>::Accept(BaseElement* base_element);
template IRTStorage TemplateVisitor<IRTStorage>::Accept(
    BaseElement* base_element);
template Temporary TemplateVisitor<Temporary>::Accept(BaseElement* base_element);
