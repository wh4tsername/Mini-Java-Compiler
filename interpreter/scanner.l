%{
    #include <cerrno>
    #include <climits>
    #include <cstdlib>
    #include <cstring>
    #include <string>
    #include <iostream>
    #include "driver.hh"
    #include "parser.hh"
%}

%option noyywrap nounput noinput batch debug

%option c++
%option yyclass="Scanner"

%{
  // A number symbol corresponding to the value in S.
  yy::parser::symbol_type make_NUMBER(
    const std::string &s,
    const yy::parser::location_type& loc
  );
%}

IDENT  [a-zA-Z][_a-zA-Z0-9]*
NUMBER ([1-9][0-9]*)|0
BLANK  [ \t\r]

%{
  // Code run each time a pattern is matched.
  # define YY_USER_ACTION  loc.columns(yyleng);
%}
%%
%{
  // A handy shortcut to the location held by the driver.
  yy::location& loc = driver.location;
  // Code run each time yylex is called.
  loc.step();
%}

{BLANK}+   loc.step();
\n+        loc.lines(yyleng); loc.step();

"class"    return yy::parser::make_CLASS   (loc);
"public"   return yy::parser::make_PUBLIC  (loc);
"static"   return yy::parser::make_STATIC  (loc);
"void"     return yy::parser::make_VOID    (loc);
"main"     return yy::parser::make_MAIN    (loc);
"extends"  return yy::parser::make_EXTENDS (loc);

"int"      return yy::parser::make_INT  (loc);
"boolean"  return yy::parser::make_BOOL (loc);

"assert"   return yy::parser::make_ASSERT (loc);

"if"       return yy::parser::make_IF     (loc);
"else"     return yy::parser::make_ELSE   (loc);

"while"    return yy::parser::make_WHILE  (loc);

"System.out.println" return yy::parser::make_PRINT (loc);

"return"   return yy::parser::make_RETURN (loc);

"length"   return yy::parser::make_LENGTH (loc);

"new"      return yy::parser::make_NEW    (loc);
"this"     return yy::parser::make_THIS   (loc);

"true"     return yy::parser::make_TRUE   (loc);
"false"    return yy::parser::make_FALSE  (loc);

"{"        return yy::parser::make_LPAREN_F  (loc);
"}"        return yy::parser::make_RPAREN_F  (loc);
"("        return yy::parser::make_LPAREN    (loc);
")"        return yy::parser::make_RPAREN    (loc);
"["        return yy::parser::make_LPAREN_S  (loc);
"]"        return yy::parser::make_RPAREN_S  (loc);
";"        return yy::parser::make_SEMICOLON (loc);
","        return yy::parser::make_COMMA  (loc);
"="        return yy::parser::make_ASSIGN (loc);
"."        return yy::parser::make_DOT    (loc);
"!"        return yy::parser::make_NOT    (loc);
"&&"       return yy::parser::make_AND    (loc);
"||"       return yy::parser::make_OR     (loc);
"<"        return yy::parser::make_LT     (loc);
">"        return yy::parser::make_GT     (loc);
"<="       return yy::parser::make_LE     (loc);
">="       return yy::parser::make_GE     (loc);
"=="       return yy::parser::make_EQ     (loc);
"!="       return yy::parser::make_NEQ    (loc);
"+"        return yy::parser::make_PLUS   (loc);
"-"        return yy::parser::make_MINUS  (loc);
"*"        return yy::parser::make_MUL    (loc);
"/"        return yy::parser::make_DIV    (loc);
"%"        return yy::parser::make_MOD    (loc);

{IDENT}    return yy::parser::make_IDENT(yytext, loc);
{NUMBER}   return make_NUMBER(yytext, loc);
<<EOF>>    return yy::parser::make_END (loc);
.          throw yy::parser::syntax_error(loc, "invalid character: " + std::string(yytext));
%%

yy::parser::symbol_type make_NUMBER(const std::string &s, const yy::parser::location_type& loc) {
  errno = 0;
  long n = strtol(s.c_str(), NULL, 10);
  if (! (INT_MIN <= n && n <= INT_MAX && errno != ERANGE)) {
    throw yy::parser::syntax_error(loc, "integer is out of range: " + s);
  }
  return yy::parser::make_NUMBER((int) n, loc);
}
