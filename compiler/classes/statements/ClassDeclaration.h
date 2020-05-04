#pragma once

#include "ListOfStatements.h"
#include "Statement.h"

#include <string>

class ClassDeclaration : public Statement {
 public:
  explicit ClassDeclaration(std::string class_name,
                            ListOfStatements* declarations);

  void Accept(Visitor* visitor) override;
  void PreAccept(Visitor* visitor) override;

  std::string class_name_;
  ListOfStatements* declarations_;
};
