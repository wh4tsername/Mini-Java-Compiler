#include "Program.h"

Program::Program(ListOfStatements* main_class,
                 ListOfStatements* class_declarations)
    : main_class_(main_class), class_declarations_(class_declarations) {}

void Program::Run() {
  class_declarations_->Run();
  main_class_->Run();
}
