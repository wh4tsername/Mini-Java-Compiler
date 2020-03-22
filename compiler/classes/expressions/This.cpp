#include "This.h"

void This::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
