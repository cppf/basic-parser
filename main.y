%{
#include "mast.h"

Ast *yyroot;
extern int yylex();
void yyerror(const char *s);
%}

%token BOOLV INTEGERV LONGV SINGLEV DOUBLEV STRINGV ID BR

%left AND OR XOR IMP EQV
%left NOT
%left EQ LT GT LE GE NE
%left MOD
%left ADD SUB
%left MUL DIV IDIV
%left POW

%union {
  bool    b;
  int     i;
  long    l;
  float   f;
  double  d;
  char   *s;
  Ast    *a;
}

%type<a> p s x e
%start p

%%
p:    { yyroot = NULL; }
  | s { yyroot = $1; }
  ;
s:  x EQ e  { $$ = new Let($1, $3); }
  ;
x:  ID      { $$ = new Id(yylval.s); }
  ;
e:  e AND e   { $$ = new Op2(pand, $1, $3); }
  | e OR e    { $$ = new Op2(por, $1, $3); }
  | e XOR e   { $$ = new Op2(pxor, $1, $3); }
  | e IMP e   { $$ = new Op2(pimp, $1, $3); }
  | e EQV e   { $$ = new Op2(peqv, $1, $3); }
  | NOT e     { $$ = new Op1(pnot, $2); }
  | e EQ e    { $$ = new Op2(peq, $1, $3); }
  | e LT e    { $$ = new Op2(plt, $1, $3); }
  | e GT e    { $$ = new Op2(pgt, $1, $3); }
  | e LE e    { $$ = new Op2(ple, $1, $3); }
  | e GE e    { $$ = new Op2(pge, $1, $3); }
  | e NE e    { $$ = new Op2(pne, $1, $3); }
  | e MOD e   { $$ = new Op2(pmod, $1, $3); }
  | e ADD e   { $$ = new Op2(padd, $1, $3); }
  | e SUB e   { $$ = new Op2(psub, $1, $3); }
  | e MUL e   { $$ = new Op2(pmul, $1, $3); }
  | e DIV e   { $$ = new Op2(pdiv, $1, $3); }
  | e IDIV e  { $$ = new Op2(pidiv, $1, $3); }
  | e POW e   { $$ = new Op2(ppow, $1, $3); }
  | '(' e ')' { $$ = $2; }
  | ADD e     { $$ = new Op1(ppos, $2); }
  | SUB e     { $$ = new Op1(pneg, $2); }
  | BOOLV     { $$ = new Literal(yylval.b); }
  | INTEGERV  { $$ = new Literal((long)yylval.i); }
  | LONGV     { $$ = new Literal(yylval.l); }
  | SINGLEV   { $$ = new Literal(yylval.f); }
  | DOUBLEV   { $$ = new Literal(yylval.d); }
  | STRINGV   { $$ = new Literal(new string(yylval.s)); }
  | ID        { $$ = new Id(yylval.s); }
  ;

%%
void yyerror(const char *s) {
  fprintf(stderr, "error: %s\n", s);
}
