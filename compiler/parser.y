%skeleton "lalr1.cc"
%require "3.5.1"

%defines
%define api.token.constructor
%define api.value.type variant
%define parse.assert

%code requires {
    #include <string>
    class Scanner;
    class Driver;
    #include "declarations.h"
    #include "classes/statements/Statement.h"

    #ifdef YYDEBUG
       yydebug = 1;
    #endif
}

%define parse.trace
%define parse.error verbose

%code {
    #include "driver.hh"
    #include "location.hh"

    #include "nodes.h"

    static yy::parser::symbol_type yylex(Scanner& scanner, Driver& driver) {
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

    LENGTH ".length"

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

%nonassoc NO_ELSE
%nonassoc "else"

%token <std::string> IDENT "identifier"
%token <int> NUMBER "number"

%nterm <Expression*> expression
%nterm <LogicalExpression*> logical_expression
%nterm <ArrayAccessExpression*> array_access
%nterm <Type*> type_identifier simple_type type
%nterm <ArrayType*> array_type
%nterm <MethodInvocation*> method_invocation
%nterm <MethodExpression*> method_expression
%nterm <Lvalue*> lvalue
%nterm <VariableDeclaration*> variable_declaration local_variable_declaration
%nterm <Statement*> statement declaration bracket_statement
%nterm <ListOfStatements*> statements declarations class_declarations
%nterm <Formals*> formals
%nterm <MethodDeclaration*> method_declaration
%nterm <ClassDeclaration*> class_declaration
%nterm <MainClass*> main_class
%nterm <Program*> program
%nterm <MethodDeclaration*> main_method
%nterm <FieldAccess*> field_access

%%
%start program;
program:
    main_class class_declarations {$$ = new Program($1, $2); driver.program_ = $$;}

class_declarations:
    class_declarations class_declaration {$1->AddStatement($2); $$ = $1;}
    | %empty {$$ = new ListOfStatements();}

main_class:
    "class" "identifier" "{" main_method declarations "}" {$$ = new MainClass($2, $4, $5);}

main_method:
    "public" "static" "void" "main" "(" ")" "{" statements "}" {$$ = new MethodDeclaration(std::string("main"), new Type("void"), NULL, $8); }

class_declaration:
    "class" "identifier" "{" declarations "}" {$$ = new ClassDeclaration($2, $4);}

declarations:
    declarations declaration {$1->AddStatement($2); $$ = $1;}
    | %empty {$$ = new ListOfStatements();}

declaration:
    variable_declaration {$$ = $1;}
    | method_declaration {$$ = $1;}

method_declaration:
    "public" type "identifier" "(" ")" "{" statements "}" {$$ = new MethodDeclaration($3, $2, NULL, $7);}
    | "public" type "identifier" "(" formals ")" "{" statements "}" {$$ = new MethodDeclaration($3, $2, $5, $8);}

variable_declaration:
    type "identifier" ";" {$$ = new VariableDeclaration($1, $2);}

formals:
    formals "," type "identifier" {$1->AddFormal($3, $4); $$ = $1;}
    | type "identifier" {$$ = new Formals(); $$->AddFormal($1, $2);}

type:
    simple_type {$$ = $1;}
    | array_type {$$ = $1;}

simple_type:
    "int" {$$ = new Type("int");}
    | "boolean" {$$ = new Type("boolean");}
    | "void" {$$ = new Type("void");}
    | type_identifier {$$ = $1;}

array_type:
    simple_type "[]" {$$ = new ArrayType($1);}

type_identifier:
    "identifier" {$$ = new Type($1);}

statements:
    statements statement {$1->AddStatement($2); $$ = $1;}
    | %empty {$$ = new ListOfStatements();}

statement:
    "assert" "(" expression ")" ";" {$$ = new AssertStatement($3);}
    | local_variable_declaration {$$ = $1;}
    | "if"  "(" expression ")" bracket_statement %prec NO_ELSE {$$ = new IfStatement($3, $5, NULL);}
    | "if"  "(" expression ")" bracket_statement "else" bracket_statement {$$ = new IfStatement($3, $5, $7);}
    | "while"  "(" expression ")" bracket_statement {$$ = new WhileStatement($3, $5);}
    | "System.out.println" "(" expression ")" ";" {$$ = new PrintStatement($3);}
    | lvalue "=" expression ";" {$$ = new AssignmentStatement($1, $3);}
    | "return" expression ";" {$$ = new ReturnStatement($2);}
    | method_invocation ";" {$$ = $1;}

bracket_statement:
    "{" statements "}" {$$ = new ScopeListOfStatements($2);}

local_variable_declaration:
    variable_declaration {$$ = $1;}

method_invocation:
    "identifier" "." "identifier" "(" method_expression ")" {$$ = new MethodInvocation($1, $3, $5);}
    | "this" "." "identifier" "(" method_expression ")" {$$ = new MethodInvocation("this", $3, $5);}
    | "identifier" "." "identifier" "(" ")" {$$ = new MethodInvocation($1, $3, NULL);}
    | "this" "." "identifier" "(" ")" {$$ = new MethodInvocation("this", $3, NULL);}

method_expression:
    method_expression "," expression {$1->AddExpression($3); $$ = $1;}
    | expression {$$ = new MethodExpression($1);}

lvalue:
    "identifier" {$$ = new Lvalue($1, NULL, NULL, 0);}
    | array_access {$$ = new Lvalue("", $1, NULL, 1);}
    | field_access {$$ = new Lvalue("", NULL, $1, 2);}

expression:
    "identifier" {$$ = new VariableExpression($1);}
    | "number" {$$ = new NumeralExpression($1);}
    | "-" expression %prec UMINUS {$$ = new ArithmeticalExpression("@", NULL, $2);}
    | expression "+" expression {$$ = new ArithmeticalExpression("+", $1, $3);}
    | expression "-" expression {$$ = new ArithmeticalExpression("-", $1, $3);}
    | expression "*" expression {$$ = new ArithmeticalExpression("*", $1, $3);}
    | expression "/" expression {$$ = new ArithmeticalExpression("/", $1, $3);}
    | expression "%" expression {$$ = new ArithmeticalExpression("%", $1, $3);}
    | "(" expression ")" {$$ = $2;}
    | "identifier" ".length" {$$ = new LengthExpression($1);}
    | array_access {$$ = $1;}
    | "new" simple_type "[" expression "]" {$$ = new NewArrayExpression($2, $4);}
    | "new" type_identifier "(" ")" {$$ = new NewVariableExpression($2);}
    | field_access {$$ = $1;}
    | logical_expression {$$ = $1;}
    | method_invocation {$$ = $1;}

field_access:
    "this" "." "identifier" {$$ = new FieldAccess($3);}

array_access:
    "identifier" "[" expression "]" {$$ = new ArrayAccessExpression($1, $3);}

logical_expression:
    expression "&&" expression {$$ = new LogicalExpression("&&", $1, $3);}
    | expression "||" expression {$$ = new LogicalExpression("||", $1, $3);}
    | expression "<" expression {$$ = new LogicalExpression("<", $1, $3);}
    | expression ">" expression {$$ = new LogicalExpression(">", $1, $3);}
    | expression "<=" expression {$$ = new LogicalExpression("<=", $1, $3);}
    | expression ">=" expression {$$ = new LogicalExpression(">=", $1, $3);}
    | expression "==" expression {$$ = new LogicalExpression("==", $1, $3);}
    | expression "!=" expression {$$ = new LogicalExpression("!=", $1, $3);}
    | "!" expression %prec NOT {$$ = new LogicalExpression("!", NULL, $2);}
    | "true" {$$ = new LogicalExpression("true", NULL, NULL);}
    | "false" {$$ = new LogicalExpression("false", NULL, NULL);}
%%
