%{
	#include <stdlib.h>
	#include <string.h>
	#include <stdio.h>
%}

IDENT [a-zA-Z][_a-zA-Z0-9]*
NUMBER ([1-9][0-9]*)|0
REAL (([1-9][0-9]*)|0)\.[0-9]*
STR \"[^"]*\"

%option noyywrap

%%
"MODULE"    { return MODULE; }
"IMPORT"    { return IMPORT; }
"VAR"       { return VAR; }
"BEGIN"     { return T_BEGIN; }
"END"       { return END; }
"PRINT"     { return PRINT; }
"IF"        { return IF; }
"THEN"      { return THEN; }
"ELSE"      { return ELSE; }
"DO"        { return DO; }
"WHILE"     { return WHILE; }
"REPEAT"    { return REPEAT; }
"UNTIL"     { return UNTIL; }
"INTEGER"   { return T_INTEGER; }
"REAL"      { return T_REAL; }
"BOOL"      { return T_BOOL; }
"STRING"    { return T_STRING; }
"="         { return '='; }
"<"         { return '<'; }
">"         { return '>'; }
"<="        { return T_LE; }
">="        { return T_GE; }
"AND"       { return T_AND; }
"OR"        { return T_OR; }
"NOT"       { return T_NOT; }
"TRUE"      { return T_TRUE; }
"FALSE"     { return T_FALSE; }
"+"         { return '+'; }
"-"         { return '-'; }
"/"         { return '/'; }
"*"         { return '*'; }
"MOD"       { return MOD; }
"CON"       { return CON; }
"("         { return '('; }
")"         { return ')'; }
"["         { return '['; }
"]"         { return ']'; }
";"         { return ';'; }
":"         { return ':'; }
"."         { return '.'; }
":="        { return ASSIGNMENT_SYMBOL; }
" "         { /* space - do nothing */ }
"\t"        { /* tab symbol - do nothing */ }
"\n"        { /* end of line symbol - do nothing */}
{IDENT}     { strcpy(yylval.id_name, yytext); return IDENT; }
{NUMBER}    { yylval.int_value = atoi(yytext); return NUMBER; }
{REAL}      { yylval.double_value = atof(yytext); return REAL; }
{STR}       { strcpy(yylval.id_name, yytext); return STR; }
.           { printf("Lexical error: %s\n", yytext); exit(1); }

%%
