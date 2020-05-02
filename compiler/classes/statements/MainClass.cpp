#include "MainClass.h"

MainClass::MainClass(std::string main_class_name,
                     MethodDeclaration* main,
                     ListOfStatements* declarations)
    : main_class_name_(std::move(main_class_name)),
      main_(main),
      declarations_(declarations) {}

void MainClass::Accept(Visitor* visitor) { visitor->Visit(this); }
