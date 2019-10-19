%{
#include <stdio.h>
extern int yylex();
extern char *yytext;
%}

%token NAME
%token INTEGER
%token FLOAT
%token STRING
%token BOOLEAN
%token COMMENT

%%

S: INTEGER | %empty { printf("got number %s\n", yytext); }

%%
int main(int argc, char **argv) {
  char *input = argc > 1? argv[1] : "input.bas";
  yyin = fopen(input, "r");
  yyparse();
  return 0;
}
