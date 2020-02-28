%skeleton "lalr1.cc"
%require "3.0.4"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    class Scanner;
    class Driver;
//    class Expression;
//    class NumberExpression;
//    class AddExpression;
//    class SubstractExpression;

    #ifdef YYDEBUG
       yydebug = 1;
    #endif
}

//%define parse.trace
//%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

//    #include "expressions/NumberExpression.h"
//    #include "expressions/AddExpression.h"
//    #include "expressions/MulExpression.h"
//    #include "expressions/DivExpression.h"
//    #include "expressions/SubstractExpression.h"

    static yy::parser::symbol_type yylex(Scanner &scanner, Driver& driver) {
        return scanner.ScanToken();
    }
}

%lex-param { Scanner &scanner }
%lex-param { Driver &driver }
%parse-param { Scanner &scanner }
%parse-param { Driver &driver }

%locations

%define api.token.prefix {TOK_}

%token
    END 0 "end of file"

    CLASS "class"
    PUBLIC "public"
    STATIC "static"
    VOID "void"
    MAIN "main"
    EXTENDS "extends"

    INT "int"
    BOOL "boolean"

    ASSERT "assert"

    IF "if"
    ELSE "else"

    WHILE "while"

    PRINT "System.out.println"

    RETURN "return"

    LENGTH "length"

    NEW "new"
    THIS "this"

    TRUE "true"
    FALSE "false"

    LPAREN_F "{"
    RPAREN_F "}"
    LPAREN "("
    RPAREN ")"
    LPAREN_S "["
    RPAREN_S "]"
    SEMICOLON ";"
    COMMA ","
    ASSIGN "="
    DOT "."
    NOT "!"
    AND "&&"
    OR "||"
    LT "<"
    GT ">"
    LE "<="
    GE ">="
    EQ "=="
    NEQ "!="
    PLUS "+"
    MINUS "-"
    MUL "*"
    DIV "/"
    MOD "%"
;

%left AND
%left OR
%left EQ NEQ ASSIGN
%left LE GE LT GT
%left PLUS MINUS
%left MUL DIV MOD
%right UMINUS NOT
%left DOT
%nonassoc "["

%token <std::string> IDENT "identifier"
%token <int> NUMBER "number"
//%nterm <Expression*> exp

%%
%start program;
program:
    main_class class_declarations {}

class_declarations:
    class_declarations class_declaration {}
    | %empty {}

main_class:
    "class" "identifier" "{" "public" "static" "void" "main" "(" ")" "{" statements "}" "}" {}

class_declaration:
    "class" "identifier" "{" declarations "}" {}
    | "class" "identifier" "extends" "identifier" "{" declarations "}" {}

declarations:
    declarations declaration {}
    | %empty {}

declaration:
    variable_declaration {}
    | method_declaration {}

method_declaration:
    "public" type "identifier" "(" ")" "{" statements "}" {}
    | "public" type "identifier" "(" formals ")" "{" statements "}" {}

variable_declaration:
    type "identifier" ";" {}

formals:
    formals "," type "identifier" {}
    | type "identifier" {}

type:
    simple_type {}
    | array_type {}

simple_type:
    "int" {}
    | "boolean" {}
    | "void" {}
    | type_identifier {}

array_type:
    simple_type "[" "]" {}

type_identifier: "identifier" {}

statements:
    statements statement {}
    | %empty {}

statement:
    "assert" "(" expression ")" {}
    | local_variable_declaration {}
    | "if"  "(" expression ")" statement {}
    | "if"  "(" logical_expression ")" statement {}
    | "if"  "(" expression ")" statement "else" statement {}
    | "if"  "(" logical_expression ")" statement "else" statement {}
    | "while"  "(" expression ")" statement {}
    | "while"  "(" logical_expression ")" statement {}
    | "System.out.println" "(" expression ")" ";" {}
    | lvalue "=" expression ";" {}
    | lvalue "=" logical_expression ";" {}
    | "return" expression ";" {}
    | "return" logical_expression ";" {}
    | method_invocation ";" {}
    | "{" statements "}" {}

local_variable_declaration:
    variable_declaration {}

method_invocation:
    expression "." "identifier" "(" method_expression ")" {}
    | expression "." "identifier" "(" ")" {}

method_expression:
    method_expression "," expression {}
    | expression {}

lvalue:
    expression {}

expression:
    "identifier" {}
    | "number" {}
    | "-" expression %prec UMINUS {}
    | expression "+" expression {}
    | expression "-" expression {}
    | expression "*" expression {}
    | expression "/" expression {}
    | expression "%" expression {}
    | "(" expression ")" {}
    | array_access "." "length" {}
    | array_access {}
    | "new" simple_type "[" expression "]" {}
    | "new" type_identifier "(" ")" {}
    | "this" {}
    | method_invocation {}

array_access:
    expression "[" expression "]" {}

logical_expression:
    expression "&&" expression {}
    | expression "||" expression {}
    | expression "<" expression {}
    | expression ">" expression {}
    | expression "<=" expression {}
    | expression ">=" expression {}
    | expression "==" expression {}
    | expression "!=" expression {}
    | logical_expression "&&" expression {}
    | logical_expression "||" expression {}
    | logical_expression "<" expression {}
    | logical_expression ">" expression {}
    | logical_expression "<=" expression {}
    | logical_expression ">=" expression {}
    | logical_expression "==" expression {}
    | logical_expression "!=" expression {}
    | expression "&&" logical_expression {}
    | expression "||" logical_expression {}
    | expression "<" logical_expression {}
    | expression ">" logical_expression {}
    | expression "<=" logical_expression {}
    | expression ">=" logical_expression {}
    | expression "==" logical_expression {}
    | expression "!=" logical_expression {}
    | "(" logical_expression ")" {}
    | "!" logical_expression %prec NOT {}
    | "true" {}
    | "false" {}
%%
