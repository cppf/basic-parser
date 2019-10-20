%{
#include <stdio.h>
#include <stdlib.h>

#define YYSTYPE int
extern int yylex();
extern char *yytext;
void yyerror(char *s);
%}

%token INTEGER PLUS

%%

S: Expr '\n'          { printf("=> %d\n", $1); }
   ;

Expr: INTEGER         { $$ = atoi(yytext); }
    | Expr PLUS Expr  { $$ = $1 + $3; }
    ;

%%

void yyerror(char *s) {
  fprintf(stderr, "error: %s\n", s);
}
