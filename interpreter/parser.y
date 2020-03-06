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
    class Expression;
    class NumberExpression;
    class AritmeticalExpression;

    #ifdef YYDEBUG
       yydebug = 1;
    #endif
}

%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

    #include "class/expressions/NumeralExpression.h"
    #include "class/expressions/ArithmeticalExpression.h"

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
    DOUBLE_PAREN_S "[]"
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
%right "["

%token <std::string> IDENT "identifier"
%token <int> NUMBER "number"

%nterm <Expresion*> expression
%nterm <LogicalExpression*> logical_expression

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
    simple_type "[]" {}

type_identifier:
    "identifier" {}

statements:
    statements statement {}
    | %empty {}

statement:
    "assert" "(" expression ")" {}
    | local_variable_declaration {}
    | "if"  "(" expression ")" "{" statement1 "}" {}
    | "if"  "(" expression ")" "{" statement1 "}" "else" "{" statement1 "}" {}
    | "while"  "(" expression ")" statement {}
    | "System.out.println" "(" expression ")" ";" {}
    | lvalue "=" expression ";" {}
    | "return" expression ";" {}
    | method_invocation ";" {}
    | "{" statements "}" {}

statement1:
    "assert" "(" expression ")" {}
    | local_variable_declaration {}
    | "if"  "(" expression ")" "{" statement1 "}" {}
    | "if"  "(" expression ")" "{" statement1 "}" "else" "{" statement1 "}" {}
    | "while"  "(" expression ")" statement {}
    | "System.out.println" "(" expression ")" ";" {}
    | lvalue "=" expression ";" {}
    | "return" expression ";" {}
    | method_invocation ";" {}

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
    | "number" {$$ = new NumberExpression($1);}
    | "-" expression %prec UMINUS {$$ = new ArithmeticalExpression("@", $2, NULL);}
    | expression "+" expression {$$ = new ArithmeticalExpression("+", $1, $3);}
    | expression "-" expression {$$ = new ArithmeticalExpression("-", $1, $3);}
    | expression "*" expression {$$ = new ArithmeticalExpression("*", $1, $3);}
    | expression "/" expression {$$ = new ArithmeticalExpression("/", $1, $3);}
    | expression "%" expression {$$ = new ArithmeticalExpression("%", $1, $3);}
    | "(" expression ")" {$$ = $2;}
    | expression "." "length" {}
    | array_access {}
    | "new" simple_type "[" expression "]" {}
    | "new" type_identifier "(" ")" {}
    | "this" {}
    | logical_expression {}
    | method_invocation {}

array_access:
    expression "[" expression "]" {}

logical_expression:
    expression "&&" expression {$$ = new LogicalExpression("&&", $1, $3);}
    | expression "||" expression {$$ = new LogicalExpression("||", $1, $3);}
    | expression "<" expression {$$ = new LogicalExpression("<", $1, $3);}
    | expression ">" expression {$$ = new LogicalExpression(">", $1, $3);}
    | expression "<=" expression {$$ = new LogicalExpression("<=", $1, $3);}
    | expression ">=" expression {$$ = new LogicalExpression(">=", $1, $3);}
    | expression "==" expression {$$ = new LogicalExpression("==", $1, $3);}
    | expression "!=" expression {$$ = new LogicalExpression("!=", $1, $3);}
    | "!" expression %prec NOT {$$ = new LogicalExpression("!", $2, NULL);}
    | "true" {$$ = new LogicalExpression("true", NULL, NULL);}
    | "false" {$$ = new LogicalExpression("false", NULL, NULL);}
%%
