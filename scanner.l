%{
#include "parser.tab.h"
#include "lutil.h"
int line = 0;
%}

D   [0-9]
A   [A-Za-z_]
TYP [!@#$%&?]
INT [-+]?{D}+
FLT [-+]?({D}*\.)?{D}+([eE]{INT})?
STR \"(\\.|[^"\\])*\"

%%

[ \t]                                         ;
\n                                            { line++; return BR; }
\'[^\n]*                                      { yylval.s = yytext+1; return COMMENT_QUOTE; }
(?i:rem)[\ \t]+[^\n]*                         { yylval.s = yytext+4; return COMMENT_REM; }
(?i:declare|sub|function|type|end)            { printf("keyword: %s\n", yytext); }
(?i:dim|shared|redim|static|let|const)        { printf("keyword: %s\n", yytext); }
(?i:input|print|using)                        { printf("keyword: %s\n", yytext); }
(?i:open|access|read|write|close)             { printf("keyword: %s\n", yytext); }
(?i:output|input|random|binary|append)        { printf("keyword: %s\n", yytext); }
(?i:goto|gosub|return|exit)                   { printf("keyword: %s\n", yytext); }
(?i:if|then|elseif|else|endif|select|case)    { printf("keyword: %s\n", yytext); }
(?i:for|to|step|nextwhile|wend|do|loop|until) { printf("keyword: %s\n", yytext); }
(?i:as|integer|unsigned|single|double)        { printf("keyword: %s\n", yytext); }
(?i:string|char|boolean)                      return KEYWORD;
[,;]                                          return SEP;
(=|<|>|<=|>=|<>)                              return BIN_EQU;
(?i:and|or|xor|imp|eqv)                       return BIN_LOG;
(?i:mod)                                      return BIN_ARI;
[\+\-]                                        return BIN_ADD;
[\*\/\\]                                      return BIN_MUL;
[\^]                                          return BIN_POW;
(?i:not)                                      return UNA_LOG;
(?i:true|false)                               return BOOL;
{STR}                                         return STRING;
{INT}&                { yylval.l = strtol(pop(yytext, 1), NULL, 0); return LONG; }
{INT}                 { yylval.i = (int) strtol(yytext, NULL, 0); return INTEGER; }
{FLT}#                { yylval.d = strtod(pop(yytext, 1), NULL, 0); return DOUBLE; }
{FLT}                 { yylval.f = strtof(yytext, NULL, 0); return SINGLE; }
{A}({A}|{D})*{TYP}?   { yylval.s = strdup(yytext); return ID; }
.                     error(line, yytext);

%%

void error(int l, char *s) {
  printf("l%d: unreconized character %s", l, s);
}
