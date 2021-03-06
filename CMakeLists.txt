cmake_minimum_required(VERSION 3.10.2)

set(CMAKE_CXX_STANDARD_REQUIRED 17)

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

set(
        NODES

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
        compiler/classes/expressions/FieldAccess.cpp
        compiler/classes/Type.cpp
        compiler/classes/ArrayType.cpp
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
        compiler/classes/ScopeListOfStatements.cpp
)

set(
        VISITORS

        compiler/visitors/PrintTreeVisitor.cpp
#        compiler/visitors/FunctionProcessingVisitor.cpp
#        compiler/visitors/SymbolTreeVisitor.cpp
        compiler/visitors/TemplateVisitor.cpp

        compiler/visitors/NewSymbolTreeVisitor.cpp
        compiler/visitors/NewFunctionProcessingVisitor.cpp
        compiler/visitors/TypeCheckingVisitor.cpp
)

set(
        OBJECTS

        compiler/objects/Object.cpp
        compiler/objects/Method.cpp
        compiler/objects/Class.cpp

        compiler/objects/PrimitiveObject.cpp
        compiler/objects/PrimitiveSimpleObject.cpp
        compiler/objects/PrimitiveArrayObject.cpp

        compiler/objects/values/Value.cpp
        compiler/objects/values/VariableValue.cpp
        compiler/objects/values/ArrayValue.cpp
)

set(
        DRIVERS

        compiler/driver.cpp

        compiler/symbol_table/Symbol.cpp

        compiler/symbol_table/NewScopeLayer.cpp
        compiler/symbol_table/NewScopeLayerTree.cpp

        compiler/function_processing/FrameEmulator.cpp
        compiler/function_processing/FunctionStorage.cpp
        compiler/function_processing/FunctionTable.cpp

        compiler/function_processing/ClassStorage.cpp
)

add_executable(
        Compiler
        main.cpp
        ${DRIVERS}
        ${NODES}
        ${VISITORS}
        ${OBJECTS}
        ${BISON_Parser_OUTPUTS}
        ${FLEX_Scanner_OUTPUTS}
)

target_include_directories(
        Compiler PRIVATE ${Interpreter_SOURCE_DIR}
)
