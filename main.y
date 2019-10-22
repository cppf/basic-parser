%{
#include "main.h"

Ast *yyroot;
extern int yylex();
void yyerror(const char *s);
%}

%token BOOLV INTEGERV LONGV SINGLEV DOUBLEV STRINGV
// %token AND OR XOR IMP EQV NOT EQ LT GT LE GE NE
// %token MOD ADD SUB MUL DIV IDIV POW
%token BR

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

%type<a> e
%start s

%%
s:      { yyroot = NULL; }
  | e   { yyroot = $1; }
  ;
e:  e AND e   { $$ = new Apply("and", {$1, $3}); }
  | e OR e    { $$ = new Apply("or", {$1, $3}); }
  | e XOR e   { $$ = new Apply("xor", {$1, $3}); }
  | e IMP e   { $$ = new Apply("imp", {$1, $3}); }
  | e EQV e   { $$ = new Apply("eqv", {$1, $3}); }
  | e NOT e   { $$ = new Apply("not", {$1, $3}); }
  | e EQ e    { $$ = new Apply("=", {$1, $3}); }
  | e LT e    { $$ = new Apply("<", {$1, $3}); }
  | e GT e    { $$ = new Apply(">", {$1, $3}); }
  | e LE e    { $$ = new Apply("<=", {$1, $3}); }
  | e GE e    { $$ = new Apply(">=", {$1, $3}); }
  | e NE e    { $$ = new Apply("<>", {$1, $3}); }
  | e MOD e   { $$ = new Apply("mod", {$1, $3}); }
  | e ADD e   { $$ = new Apply("+", {$1, $3}); }
  | e SUB e   { $$ = new Apply("-", {$1, $3}); }
  | e MUL e   { $$ = new Apply("*", {$1, $3}); }
  | e DIV e   { $$ = new Apply("/", {$1, $3}); }
  | e IDIV e  { $$ = new Apply("\\", {$1, $3}); }
  | e POW e   { $$ = new Apply("^", {$1, $3}); }
  | '(' e ')' { $$ = $2; }
  | BOOLV     { $$ = new Literal({BOOL, {b: yylval.b}}); }
  | INTEGERV  { $$ = new Literal({INTEGER, {i: yylval.i}}); }
  | LONGV     { $$ = new Literal({LONG, {l: yylval.l}}); }
  | SINGLEV   { $$ = new Literal({SINGLE, {f: yylval.f}}); }
  | DOUBLEV   { $$ = new Literal({DOUBLE, {d: yylval.d}}); }
  | STRINGV   { $$ = new Literal({STRING, {s: new string(yylval.s)}}); }
  ;

%%
void yyerror(const char *s) {
  fprintf(stderr, "error: %s\n", s);
}
