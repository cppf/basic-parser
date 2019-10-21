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


%%
void yyerror(char *s) {
  fprintf(stderr, "error: %s\n", s);
}
