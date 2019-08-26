%{
#include <stdio.h>
extern int yylex();
%}
%%
[ \t]                                     ;
\n                                        { printf("br\n"); }
\'[^\n]*                                  { printf("comment_quote: %s\n", yytext); }
rem[\ \t]+[^\n]*                          { printf("comment_rem: %s\n", yytext); }
true|false                                { printf("boolean: %s\n", yytext); }
\"(\\.|[^"\\])*\"                         { printf("string: %s\n", yytext); }
[-+]?[0-9]+                               { printf("integer: %s\n", yytext); }
[-+]?([0-9]*[.])?[0-9]+([eE][-+]?[0-9]+)? { printf("float: %s\n", yytext); }
[A-Za-z_][A-Za-z_!@#$%&?]*                { printf("name: %s\n", yytext); }
.
%%
void main() {
  yyin = fopen("input.bas", "r");
  while(yylex());
}
