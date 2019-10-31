%{
#include "mast.h"

Ast *yyroot;
extern int yylex();
extern void yyerror(const char *s);
%}

%token DECLARE DEF SUB FUNCTION
%token DIM REDIM SHARED STATIC TYPE
%token AS BOOLEAN INTEGER LONG SINGLE DOUBLE STRING
%token IF THEN ELSEIF ELSE ENDIF SELECT CASE
%token FOR TO STEP NEXT WHILE WEND DO UNTIL LOOP
%token LET CONST INPUT LINE PRINT OPEN CLOSE
%token OUTPUT RANDOM BINARY APPEND ACCESS READ WRITE
%token GOTO GOSUB RETURN EXIT

%token BOOLEANV INTEGERV LONGV SINGLEV DOUBLEV STRINGV ID
%token REM END BR

%left AND OR XOR IMP EQV
%left NOT
%left EQ LT GT LE GE NE
%left MOD
%left ADD SUB
%left MUL DIV IDIV
%left POW

%union {
  bool    b;
  char    c;
  int     i;
  long    l;
  float   f;
  double  d;
  char   *s;
  Ast    *a;
  Asts   *as;
}

%type<a> p lin
%type<a> b proc define if select for while do
%type<a> elseifs case case_else
%type<a> s set io file branch
%type<a> n
%type<a> e litr call es x
%type<a> defb defc defs def
%type<as> lins cases pexps
%type<s> fmode facc l
%type<c> typ efrom
%start p



%%
p:
    lins          { yyroot = $1; }
  |               { yyroot = NULL; }
;
lins:
    lins BR lin   { $$ = $1->add($3); }
  | lin           { $$ = new Asts(); }
;
lin:
    x ':' b       { $$ = new Line($3, $1->s()); }
  | n b           { $$ = new Line($2, $1->s()); }
  | b             { $$ = new Line($1, NULL); }
  | BR            { $$ = new Line(); }
;



b:
    proc
  | define
  | if
  | select
  | for
  | while
  | do
  | s
;
proc:
    DECLARE SUB x defc                    { $$ = new Declare($3, $4); }
  | DECLARE FUNCTION x defc               { $$ = new Declare($3, $4); }
  | SUB x defc BR b BR END SUB            { $$ = new Proc($2, $3, $5); }
  | FUNCTION x defc BR b BR END FUNCTION  { $$ = new Proc($2, $3, $5); }
;
define:
    DIM defs                    {}
  | DIM SHARED defs             {}
  | REDIM es                    {}
  | SHARED defs                 {}
  | STATIC defs                 {}
  | TYPE x BR defb BR END TYPE  {}
;
if:
    IF e THEN s                           { $$ = new If($2, {$4}, {}); }
  | IF e THEN s ELSE s                    { $$ = new If($2, {$4}, {$6}); }
  | IF e THEN BR b BR endif               { $$ = new If($2, $5, {}); }
  | IF e THEN BR b BR ELSE BR b BR endif  { $$ = new If($2, $5, $9); }
  | IF e THEN BR b BR elseifs             { $$ = new If($2, $5, $7); }
;
select:
  SELECT CASE e BR cases BR END SELECT    { $$ = new Select($3, $5); }
;
for:
    FOR x EQ e TO e BR b BR NEXT            { $$ = new For($2, $4, $6, $2, 1, $8); }
  | FOR x EQ e TO e BR b BR NEXT x          { $$ = new For($2, $4, $6, $11, 1, $8); }
  | FOR x EQ e TO e STEP e BR b BR NEXT     { $$ = new For($2, $4, $6, $2, $8, $10); }
  | FOR x EQ e TO e STEP e BR b BR NEXT x   { $$ = new For($2, $4, $6, $13, $8, $10); }
;
while:
    WHILE e BR b BR WEND      { $$ = new While($2, $4); }
;
do:
    DO WHILE e BR b BR LOOP   { $$ = new Do($3, new Litr(true), $5); }
  | DO UNTIL e BR b BR LOOP   { $$ = new Do(new Call("not", $3), new Litr(true), $5); }
  | DO BR b BR LOOP WHILE e   { $$ = new Do(new Litr(true), $7, $3); }
  | DO BR b BR LOOP UNTIL e   { $$ = new Do(new Litr(true), new Call("not", $7), $3); }
;

elseifs:
    ELSEIF e THEN BR b BR endif             { $$ = new If($2, $5, {}); }
  | ELSEIF e THEN BR b BR ELSE BR b endif   { $$ = new If($2, $5, $9); }
  | ELSEIF e THEN BR b BR elseifs           { $$ = new If($2, $5, $7); }
;
endif:
    END IF
  | ENDIF
;

cases:
    cases BR case       { $$ = $1->add($3); }
  | cases BR case_else  { $$ = $1->add($3); }
  | case                { $$ = new Asts({$1}); }
;
case:
    CASE e BR b       { $$ = new Case($2, $4); }
  | CASE e TO e BR b  { $$ = new CaseTo($2, $4, $6); }
;
case_else:
    CASE ELSE BR b    { $$ = new CaseElse($4); }
;



s:
    set
  | io
  | file
  | branch
;
set:
    LET x EQ e    { $$ = new Let($2, $4); }
  | CONST x EQ e  { $$ = new Let($2, $4); }
  | x EQ e        { $$ = new Let($1, $3); }
;
io:
    INPUT es            { $$ = new Input("", "", $2); }
  | INPUT ';' es        { $$ = new Input("", "?", $3); }
  | INPUT e ';' es      { $$ = new Input($2, "?", $4); }
  | LINE INPUT x        { $$ = new LineInput("", "", $3); }
  | LINE INPUT ';' x    { $$ = mew LineInput("", "?", $4); }
  | LINE INPUT e ';' x  { $$ = new LineInput($3, "?", $5); }
  | LINE INPUT e ',' x  { $$ = new LineInput($3, "", $5); }
  | PRINT pexps         { $$ = Call("print", $2->add(new Litr("\n"))); }
  | PRINT pexps ','     { $$ = Call("print", $2->add(new Litr("\t"));); }
  | PRINT pexps ';'     { $$ = Call("print", $2); }
;
file:
    OPEN e fmode facc AS e  { $$ = new Call("open", $6, $2, new Litr($3), new Litr($4)); }
  | OPEN e ',' e ',' e      { $$ = new Call("open", $4, $6, $2, new Litr("RW")); }
  | CLOSE es                { $$ = new Call("close", es); /* split?? */}
  | CLOSE                   { $$ = new Call("closeall", {}); }
;
branch:
    GOTO l      { $$ = new Goto($2); }
  | GOSUB l     { $$ = new Gosub($2); }
  | RETURN      { $$ = new Return(""); }
  | RETURN l    { $$ = new Return($2); }
  | EXIT efrom  { $$ = new Exit((long) $2); }
;

fmode:
    FOR OUTPUT  { $$ = "O"; }
  | FOR INPUT   { $$ = "I"; }
  | FOR RANDOM  { $$ = "R"; }
  | FOR BINARY  { $$ = "B"; }
  | FOR APPEND  { $$ = "A"; }
  |             { $$ = "I"; }
;
facc:
    ACCESS READ         { $$ = "R"; }
  | ACCESS WRITE        { $$ = "W"; }
  | ACCESS READ WRITE   { $$ = "RW"; }
  |                     { $$ = "R"; }
;
efrom:
    DEF       { $$ = 'D'; }
  | DO        { $$ = 'd'; }
  | FOR       { $$ = 'f'; }
  | SUB       { $$ = 'S'; }
  | FUNCTION  { $$ = 'F'; }
;
pexps:
    pexps ',' e   { $$ = $1->add(new Litr("\t"))->add($3); }
  | pexps ';' e   { $$ = $1->add($3); }
  | e             { $$ = new Asts($1); }
  |               { $$ = new Asts({}); }
;
l:
    n   { $$ = $1->s(); }
  | x   { $$ = $1->s(); }
;
n:
    INTEGERV  { $$ = new Litr((long) yylval.i); }
;



e: 
    e AND e   { $$ = new Call("and", $1, $3); }
  | e OR e    { $$ = new Call("or", $1, $3); }
  | e XOR e   { $$ = new Call("xor", $1, $3); }
  | e IMP e   { $$ = new Call("imp", $1, $3); }
  | e EQV e   { $$ = new Call("eqv", $1, $3); }
  | NOT e     { $$ = new Call("not", $2); }
  | e EQ e    { $$ = new Call("=", $1, $3); }
  | e LT e    { $$ = new Call("<", $1, $3); }
  | e GT e    { $$ = new Call(">", $1, $3); }
  | e LE e    { $$ = new Call("<=", $1, $3); }
  | e GE e    { $$ = new Call(">=", $1, $3); }
  | e NE e    { $$ = new Call("<>", $1, $3); }
  | e MOD e   { $$ = new Call("mod", $1, $3); }
  | e ADD e   { $$ = new Call("+", $1, $3); }
  | e SUB e   { $$ = new Call("-", $1, $3); }
  | e MUL e   { $$ = new Call("*", $1, $3); }
  | e DIV e   { $$ = new Call("/", $1, $3); }
  | e IDIV e  { $$ = new Call("\\", $1, $3); }
  | e POW e   { $$ = new Call("^", $1, $3); }
  | '(' e ')' { $$ = $2; }
  | ADD e     { $$ = new Call("id", $2); }
  | SUB e     { $$ = new Call("neg", $2); }
  | litr
  | call
  | x
;
litr:
    BOOLEANV  { $$ = new Litr(yylval.b); }
  | INTEGERV  { $$ = new Litr((long) yylval.i); }
  | LONGV     { $$ = new Litr(yylval.l); }
  | SINGLEV   { $$ = new Litr(yylval.f); }
  | DOUBLEV   { $$ = new Litr(yylval.d); }
  | STRINGV   { $$ = new Litr(new string(yylval.s)); }
;
call:
    x '(' ')'       { $$ = new Call($1, {}); }
  | x '(' es  ')'   { $$ = new Call($1, $3); }
;


defb:
    defb BR def
  | def
;
defc:
    '(' defs ')'  {}
  | '(' ')'       {}
  |               {}
;
defs:
    defs ',' def
  | def
;
def:
    x AS typ
  | x
;
es:
    es ',' e    { $$ = ((Asts*)$1)->add($3); }
  | e           { $$ = new Asts({$1}); }
;
x:
    ID        { $$ = new Id(yylval.s); }
;
typ:
    BOOLEAN   { $$ = 'b'; }
  | INTEGER   { $$ = 'i'; }
  | LONG      { $$ = 'l'; }
  | SINGLE    { $$ = 's'; }
  | DOUBLE    { $$ = 'd'; }
  | STRING    { $$ = 's'; }
;
%%
