#pragma once

#include "statements/ListOfStatements.h"

class Program {
 public:
  Program(ListOfStatements* main_class, ListOfStatements* class_declarations);

  void Run();

 private:
  ListOfStatements* main_class_;
  ListOfStatements* class_declarations_;
};
