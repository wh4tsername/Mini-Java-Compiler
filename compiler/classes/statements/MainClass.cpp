#include "MainClass.h"

MainClass::MainClass(std::string main_class_name,
                     ListOfStatements* main_statements,
                     ListOfStatements* declarations)
    : main_class_name_(std::move(main_class_name)),
      main_statements_(main_statements),
      declarations_(declarations) {}

void MainClass::Accept(Visitor* visitor) { visitor->Visit(this); }
