#include "Program.h"

Program::Program(MainClass* main_class,
                 ListOfStatements* class_declarations)
    : main_class_(main_class), class_declarations_(class_declarations) {}

void Program::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
