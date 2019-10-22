%{
#include <stdio.h>
#include <stdlib.h>

#define YYSTYPE int
extern int yylex();
extern char *yytext;
void yyerror(char *s);
%}

%token BR COMMENT
%token DECLARE SUB FUNCTION TYPE END
%token DIM SHARED REDIM STATIC LET CONST
%token INPUT PRINT USING
%token OPEN ACCESS READ WRITE CLOSE
%token OUTPUT RANDOM BINARY APPEND
%token GOTO GOSUB RETURN EXIT
%token IF THEN ELSEIF ELSE ENDIF SELECT CASE
%token FOR TO STEP NEXT WHILE WEND DO LOOP UNTIL
%token AS BOOL INTEGER LONG SINGLE DOUBLE STRING
%token SEP BIN_EQU BIN_LOG BIN_ARI BIN_ADD BIN_MUL BIN_POW UNA_LOG
%token BOOLV STRINGV LONGV INTEGERV DOUBLEV SINGLEV
%token ID
%start s

%%
s: main_stmt s | ;
main_stmt: declare | sub | function | stmt;
declare: declare_sub | declare_fn;
declare_sub: DECLARE SUB name '(' lpar ')';
declare_fn:  DECLARE FUNCTION name_t '(' lpar ')';
sub: SUB name '(' lpar ')' BR lstmt BR END SUB;
function: FUNCTION name_t '(' lpar ')' BR lstmt BR END FUNCTION;
lstmt: stmt lstmt | ;
stmt: comment | sub_call | define | assign | io | branch | loop;
sub_call: name lexpr;
fn_call: name_t | name_t '(' lexpr ')';
define: dim | redim | shared | static | type;
dim: DIM dim_shared ldef1;
dim_shared: SHARED | ;
redim: REDIM larr1;
shared: SHARED lpar1;
static: STATIC lpar1;
type: TYPE name BR ldef1_blk BR END TYPE;
assign: let | const | assign_dir;
let: LET assign_dir;
const: CONST assign_dir;
assign_dir: var_t '=' expr;
io: input | print | open | close;
input: input_cmd | input_file;
prompt: string ',' | string ';' | ;
print: print_cmd | print_file;
print_cmd: PRINT print_fmt print_lexpr;
print_file: PRINT fnum_h, print_fmt print_lexpr;
print_fmt: USING string ';' | ;
print_lexpr: expr ',' print_lexpr | expr ';' print_lexpr | ;
open: open_long | open_short;
open_long: OPEN fname fmode1 facc AS fnum;
open_short: OPEN fmode2, fnum_h, fname;
fname: expr;
fmode1: FOR fmode1_type | ;
fmode1_type: OUTPUT | INPUT | RANDOM | BINARY | APPEND;
facc: ACCESS facc_type | ;
facc_type: READ | WRITE | READ WRITE;
fmode2: "O" | "I" | "R" | "B" | "A";
close: CLOSE lfnum1;
branch: branch_dir | branch_cond;
goto: GOTO label;
gosub: GOSUB label;
return: RETURN | RETURN label;
exit: EXIT exit_from;
exit_from: DO | FOR | FUNCTION | SUB;
branch_cond: if | select;
if: if_then | if_blk;
if_then: IF cond then_stmt else_stmt;
if_blk: IF cond then_blk BR lelseif_blk BR else_blk BR endif;
then_stmt: THEN stmt;
then_blk: THEN BR lstmt;
lelseif_blk: elseif_blk BR lelseif_blk | ;
elseif_blk: ELSEIF cond BR lstmt | ;
else_stmt: ELSE stmt | ;
else_blk: ELSE BR lstmt | ;
endif: ENDIF | END IF;
select: SELECT CASE expr BR lcase BR END SELECT;
lcase: case_expr BR lcase? | case_else;
case_expr: CASE expr (TO expr)? BR lstmt;
case_else: CASE ELSE BR lstmt;
loop: for | while | do;
for: FOR var '=' expr TO expr (STEP expr)? BR lstmt BR NEXT var?;
while: WHILE cond BR lstmt BR WEND;
do: do_entry | do_exit;
do_entry: DO (WHILE | UNTIL) cond BR lstmt BR LOOP;
do_exit: DO BR lstmt BR LOOP (WHILE | UNTIL) cond;
name_t: name dtype_s;
sym: name | name '(' ')';
sym_t: name_t | name_t '(' ')';
var: name | name '(' lexpr1 ')';
var_t: name_t | name_t '(' lexpr1 ')';
arr_t: name_t '(' lexpr1 ')';
par: sym AS dtype_n | sym_t;
def: var AS dtype_n | var_t;
larr: arr_t ',' larr1 | arr_t | ;
larr1: arr_t ',' larr1 | arr_t;
lvar: var ',' lvar1 | var | ;
lvar1: var lvar1 | var;
lpar: par ',' lpar1 | par | ;
lpar1: par ',' lpar1 | ;
ldef: def ',' ldef | def | ;
ldef1: def ',' ldef1 | def;
ldef_blk: def BR ldef1_blk | def | ;
ldef1_blk: def BR ldef1_blk | def;
lexpr: expr ',' lexpr1 | expr | ;
lexpr1: expr ',' lexpr1 | expr;
fnum: fnum_h | num;
fnum_h: '#' num;
lfnum: fnum ',' lfnum1 | fnum | ;
lfnum1: fnum ',' lfnum1 | fnum;
dtype_n: BOOL | INTEGER | LONG | SINGLE | DOUBLE | STRING;
dtype_s: '%' | '&' | '!' | '#' | '$' | '@' | '?' | ;
cond: expr;
bin_log: AND | OR | XOR | IMP | EQV;
bin_ari: MOD;
bin_add: '+' | '-';
bin_mul: '*' | '/' | '\\';
bin_pow: '^';
una_log: NOT;
una_add: '+' | '-';
expr: expr bin_log expr | expr_1;
expr_1: expr bin_ari expr | expr_2;
expr_2: expr bin_add expr | expr_3;
expr_3: expr bin_mul expr | expr_4;
expr_4: expr bin_pow expr | expr_5;
expr_5: una_log expr | expr_6;
expr_6: una_ari expr | expr_7;
expr_7: litr | var_t | fn_call | '(' expr ')';
litr: BOOLV | INTEGERV | LONGV | SINGLEV | DOUBLEV | STRINGV;

%%
void yyerror(char *s) {
  fprintf(stderr, "error: %s\n", s);
}
