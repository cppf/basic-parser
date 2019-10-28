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

%type<a> p s x e ps le
%start p

%%
p:    { yyroot = NULL; }
  | s { yyroot = $1; }
  ;
b:
    DECLARE SUB x
  | if
  | select
  ;

loop:
    for
  | while
  | do
;





if:
    IF e THEN s
  | IF e THEN s ELSE s
  | IF e THEN BR b BR endif
  | IF e THEN BR b BR elses BR endif
;
elses:
    elseif BR elses
  | elseif
  | else
;
elseif:
  ELSEIF e BR b
;
else:
  ELSE BR b
;
endif:
    END IF
  | ENDIF
;


select:
  SELECT CASE e BR cases BR END SELECT
  ;
cases:
    case BR cases
  | case
  | case_else
  ;
case:
    CASE e BR b
  | CASE e TO e BR b
  ;
case_else:
    CASE ELSE br b
  ;


for:
    FOR x EQ e TO e BR b BR NEXT
  | FOR x EQ e TO e BR b BR NEXT x
  | FOR x EQ e TO e STEP e BR b BR NEXT
  | FOR x EQ e TO e STEP e BR b BR NEXT x
;


while:
    WHILE e BR b BR WEND
;


do:
    DO WHILE e BR b BR LOOP
  | DO UNTIL e BR b BR LOOP
  | DO BR b BR LOOP WHILE e
  | DO BR b BR LOOP UNTIL e
;


s:  x EQ e  { $$ = new Let($1, $3); }
  | OPEN e fmode facc AS e
  | OPEN e, e, e
  | CLOSE es
  | CLOSE
  | GOTO l
  | GOSUB l
  | RETURN
  | RETURN l
  | EXIT efrom
  ;
fmode:
    OUTPUT
  | INPUT
  | RANDOM
  | BINARY
  | APPEND
;
facc:
    READ
  | WRITE
  | READ WRITE
;
efrom:
    DEF
  | DO
  | FOR
  | SUB
  | FUNCTION
;

x:  ID      { $$ = new Id(yylval.s); }
  ;
e:  e AND e   { $$ = new Call2(pand, $1, $3); }
  | e OR e    { $$ = new Call2(por, $1, $3); }
  | e XOR e   { $$ = new Call2(pxor, $1, $3); }
  | e IMP e   { $$ = new Call2(pimp, $1, $3); }
  | e EQV e   { $$ = new Call2(peqv, $1, $3); }
  | NOT e     { $$ = new Call1(pnot, $2); }
  | e EQ e    { $$ = new Call2(peq, $1, $3); }
  | e LT e    { $$ = new Call2(plt, $1, $3); }
  | e GT e    { $$ = new Call2(pgt, $1, $3); }
  | e LE e    { $$ = new Call2(ple, $1, $3); }
  | e GE e    { $$ = new Call2(pge, $1, $3); }
  | e NE e    { $$ = new Call2(pne, $1, $3); }
  | e MOD e   { $$ = new Call2(pmod, $1, $3); }
  | e ADD e   { $$ = new Call2(padd, $1, $3); }
  | e SUB e   { $$ = new Call2(psub, $1, $3); }
  | e MUL e   { $$ = new Call2(pmul, $1, $3); }
  | e DIV e   { $$ = new Call2(pdiv, $1, $3); }
  | e IDIV e  { $$ = new Call2(pidiv, $1, $3); }
  | e POW e   { $$ = new Call2(ppow, $1, $3); }
  | x ps      { $$ = new Call($1, $2); }
  | '(' e ')' { $$ = $2; }
  | ADD e     { $$ = new Call1(ppos, $2); }
  | SUB e     { $$ = new Call1(pneg, $2); }
  | BOOLV     { $$ = new Litr(yylval.b); }
  | INTEGERV  { $$ = new Litr((long)yylval.i); }
  | LONGV     { $$ = new Litr(yylval.l); }
  | SINGLEV   { $$ = new Litr(yylval.f); }
  | DOUBLEV   { $$ = new Litr(yylval.d); }
  | STRINGV   { $$ = new Litr(new string(yylval.s)); }
  | x         { $$ = $1; }
  ;
ps: '(' ')'     { $$ = new Asts(); }
  | '(' le ')'  { $$ = $2; }
  ;
le: e           { $$ = new Asts({$1}); }
  | le ',' e    { $$ = ((Asts*)$1)->add($3); }
  ;
%%
void yyerror(const char *s) {
  fprintf(stderr, "error: %s\n", s);
}
