cmake_minimum_required(VERSION 3.10.2)

set(BISON_EXECUTABLE /usr/local/bin/bison)

project(Compiler)
set(
        HEADERS
        compiler/driver.hh
        compiler/parser.hh
)

FIND_PACKAGE(BISON REQUIRED)
BISON_TARGET(
        Parser
        ${Compiler_SOURCE_DIR}/compiler/parser.y
        ${Compiler_SOURCE_DIR}/compiler/parser.cpp
        DEFINES_FILE ${Compiler_SOURCE_DIR}/compiler/parser.hh
)

FIND_PACKAGE(FLEX REQUIRED)
FLEX_TARGET(
        Scanner
        ${Compiler_SOURCE_DIR}/compiler/scanner.l
        ${Compiler_SOURCE_DIR}/compiler/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

add_executable(
        Compiler
        main.cpp
        compiler/driver.cpp
        compiler/classes/expressions/NumeralExpression.cpp
        compiler/classes/expressions/ArithmeticalExpression.cpp
        compiler/classes/expressions/LogicalExpression.cpp
        compiler/classes/expressions/VariableExpression.cpp
        compiler/classes/expressions/LengthExpression.cpp
        compiler/classes/expressions/ArrayAccessExpression.cpp
        compiler/classes/expressions/NewVariableExpression.cpp
        compiler/classes/expressions/NewArrayExpression.cpp
        compiler/classes/expressions/MethodInvocation.cpp
        compiler/classes/expressions/MethodExpression.cpp
        compiler/classes/Type.cpp
        compiler/classes/ArrayType.cpp
        compiler/classes/expressions/This.cpp
        compiler/classes/Lvalue.cpp
        compiler/classes/statements/VariableDeclaration.cpp
        compiler/classes/statements/ListOfStatements.cpp
        compiler/classes/statements/AssignmentStatement.cpp
        compiler/classes/statements/AssertStatement.cpp
        compiler/classes/statements/ReturnStatement.cpp
        compiler/classes/statements/PrintStatement.cpp
        compiler/classes/statements/WhileStatement.cpp
        compiler/classes/statements/IfStatement.cpp
        compiler/classes/statements/MethodDeclaration.cpp
        compiler/classes/Formals.cpp
        compiler/classes/statements/ClassDeclaration.cpp
        compiler/classes/Program.cpp
        compiler/classes/statements/MainClass.cpp
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Scanner_OUTPUTS}
        compiler/visitors/SymbolTreeVisitor.cpp
)

target_include_directories(
        Compiler PRIVATE ${Interpreter_SOURCE_DIR}
)
