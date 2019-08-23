%{
#include <stdio.h>
extern int yylex();
%}
%%
[ \t\n]                   ;
[a-zA-Z]+[\ ]+A[a-z]+wal  { printf("found one %s\n", yytext); }
.
%%
void main() {
  yyin = fopen("input.txt", "r");
  while(yylex());
}
