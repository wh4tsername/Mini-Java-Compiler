#pragma once

#include "statements/ListOfStatements.h"
#include "statements/MainClass.h"
#include "../visitors/Node.h"

class Program : public Node {
 public:
  Program(MainClass* main_class, ListOfStatements* class_declarations);

  void Run();

  void Accept(Visitor* visitor) override;

 private:
  MainClass* main_class_;
  ListOfStatements* class_declarations_;
};
