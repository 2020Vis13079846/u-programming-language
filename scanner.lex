/* Definitions */
%{
  #include <iostream>
  #include "parser.tab.c"
  using namespace std;
  extern "C" int yylex();
%}

/* Rules next */
%%
[0-9]+.[0-9]+  { yylval.floatVal = atof(yytext); return FLOAT_LITERAL; }
[0-9]+         { yylval.intVal = atoi(yytext); return INTEGER_LITERAL; }
"+"            { return PLUS; }
"-"            { return MINUS; }
"*"            { return MULT; }
"/"            { return DIV; }
";"            { return SEMI; }
[\t\r\n\f];    /* ignore whitespace */
