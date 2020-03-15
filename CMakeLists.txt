cmake_minimum_required(VERSION 3.10.2)

set(BISON_EXECUTABLE /usr/local/bin/bison)

project(Interpreter)
set(
        HEADERS
        interpreter/driver.hh
        interpreter/parser.hh
)

FIND_PACKAGE(BISON REQUIRED)
BISON_TARGET(
        Parser
        ${Interpreter_SOURCE_DIR}/interpreter/parser.y
        ${Interpreter_SOURCE_DIR}/interpreter/parser.cpp
        DEFINES_FILE ${Interpreter_SOURCE_DIR}/interpreter/parser.hh
)

FIND_PACKAGE(FLEX REQUIRED)
FLEX_TARGET(
        Scanner
        ${Interpreter_SOURCE_DIR}/interpreter/scanner.l
        ${Interpreter_SOURCE_DIR}/interpreter/scanner.cpp
)

ADD_FLEX_BISON_DEPENDENCY(Scanner Parser)

add_executable(
        Interpreter
        main.cpp
        interpreter/driver.cpp
        interpreter/classes/expressions/NumeralExpression.cpp
        interpreter/classes/expressions/ArithmeticalExpression.cpp
        interpreter/classes/expressions/LogicalExpression.cpp
        interpreter/classes/expressions/VariableExpression.cpp
        interpreter/classes/expressions/LengthExpression.cpp
        interpreter/classes/expressions/ArrayAccessExpression.cpp
        interpreter/classes/expressions/NewVariableExpression.cpp
        interpreter/classes/expressions/NewArrayExpression.cpp
        interpreter/classes/expressions/MethodInvocation.cpp
        interpreter/classes/expressions/MethodExpression.cpp
        interpreter/classes/Type.cpp
        interpreter/classes/ArrayType.cpp
        interpreter/classes/expressions/This.cpp
        interpreter/classes/Lvalue.cpp
        interpreter/classes/statements/VariableDeclaration.cpp
        interpreter/classes/statements/ListOfStatements.cpp
        interpreter/classes/statements/AssignmentStatement.cpp
        interpreter/classes/statements/AssertStatement.cpp
        interpreter/classes/statements/ReturnStatement.cpp
        interpreter/classes/statements/PrintStatement.cpp
        interpreter/classes/statements/WhileStatement.cpp
        interpreter/classes/statements/IfStatement.cpp
        interpreter/classes/statements/MethodDeclaration.cpp
        interpreter/classes/Formals.cpp
        interpreter/classes/statements/ClassDeclaration.cpp
        interpreter/classes/Program.cpp
        interpreter/classes/statements/MainClass.cpp
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Scanner_OUTPUTS}
)

target_include_directories(
        Interpreter PRIVATE ${Interpreter_SOURCE_DIR}
)
