%{
#include <stdio.h>
extern int yylex();
%}

%%



%%
int main(int argc, char **argv) {
  char *input = argc > 1? argv[1] : "input.bas";
  yyin = fopen(input, "r");
  yyparse();
  return 0;
}
