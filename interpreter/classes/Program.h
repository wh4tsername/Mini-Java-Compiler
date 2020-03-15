#pragma once

#include "statements/ListOfStatements.h"
#include "statements/MainClass.h"

class Program {
 public:
  Program(MainClass* main_class, ListOfStatements* class_declarations);

  void Run();

 private:
  MainClass* main_class_;
  ListOfStatements* class_declarations_;
};
