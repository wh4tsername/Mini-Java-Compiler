cmake_minimum_required(VERSION 3.10.2)

project(Interpreter)
set(
        HEADERS
        interpreter/driver.hh
        interpreter/parser.hh
)

find_package(BISON 3.0.0)
BISON_TARGET(
        Parser
        ${Interpreter_SOURCE_DIR}/interpreter/parser.y
        ${Interpreter_SOURCE_DIR}/interpreter/parser.cpp
        DEFINES_FILE ${Interpreter_SOURCE_DIR}/interpreter/parser.hh
)

find_package(FLEX 2.6.4)
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
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Scanner_OUTPUTS}
)

target_include_directories(
        Interpreter PRIVATE ${Interpreter_SOURCE_DIR}
)
