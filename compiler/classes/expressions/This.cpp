#include "This.h"

int This::Count() {
  return 0;
}

void This::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
