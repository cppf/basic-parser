%{
#include <stdio.h>
extern int yylex();
%}
%%
[ \t]                                     ;
\n                                        { printf("br\n"); }
\'[^\n]*                                  { printf("comment_quote: %s\n", yytext); }
(?i:rem)[\ \t]+[^\n]*                     { printf("comment_rem: %s\n", yytext); }
[,;]                                      { printf("sep: %s\n", yytext); }
(?i:and|or|xor|imp|eqv)                   { printf("bin_log: %s\n", yytext); }
(?i:mod)                                  { printf("bin_ari: %s\n", yytext); }
[\+\-]                                    { printf("bin_add: %s\n", yytext); }
[\*\/\\]                                  { printf("bin_mul: %s\n", yytext); }
[\^]                                      { printf("bin_pow: %s\n", yytext); }
(?i:not)                                  { printf("una_log: %s\n", yytext); }
(?i:true|false)                           { printf("boolean: %s\n", yytext); }
\"(\\.|[^"\\])*\"                         { printf("string: %s\n", yytext); }
[-+]?[0-9]+                               { printf("integer: %s\n", yytext); }
[-+]?([0-9]*[.])?[0-9]+([eE][-+]?[0-9]+)? { printf("float: %s\n", yytext); }
[A-Za-z_][A-Za-z_!@#$%&?]*                { printf("name: %s\n", yytext); }
.
%%
int main(int argc, char **argv) {
  char *input = argc > 1? argv[1] : "input.bas";
  yyin = fopen(input, "r");
  while(yylex());
  return 0;
}
