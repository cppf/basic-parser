%{
#include <stdio.h>
extern int yylex();
void yyerror(const char *s);
%}

%token BOOLV INTEGERV LONGV SINGLEV DOUBLEV STRINGV
%token BR
%start s

%union {
  bool    b;
  int     i;
  long    l;
  float   f;
  double  d;
  char   *s;
}

%%
s: 
  | BOOLV     { printf("boolv: %d\n", yylval.b); }
  | INTEGERV  { printf("integerv: %d\n", yylval.i); }
  | LONGV     { printf("longv: %ld\n", yylval.l); }
  | SINGLEV   { printf("singlev: %f\n", yylval.f); }
  | DOUBLEV   { printf("doublev: %lf\n", yylval.d); }
  | STRINGV   { printf("stringv: %s\n", yylval.s); }

%%
void yyerror(const char *s) {
  fprintf(stderr, "error: %s\n", s);
}
