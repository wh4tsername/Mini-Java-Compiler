#include "MainClass.h"

MainClass::MainClass(std::string main_class_name,
                     ListOfStatements* list_of_statements)
    : main_class_name_(std::move(main_class_name)),
      list_of_statements_(list_of_statements) {}

void MainClass::Run() { list_of_statements_->Run(); }

void MainClass::Accept(Visitor* visitor) {
  visitor->Visit(this);
}
