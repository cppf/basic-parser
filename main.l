%{
#include "main.tab.h"
#include "main.h"
int line = 0;
%}

D   [0-9]
A   [A-Za-z_]
TYP [!@#$%&?]
INT [-+]?{D}+
FLT [-+]?({D}*\.)?{D}+([eE]{INT})?
STR \"(\\.|[^"\\])*\"

%%
[ \t]                   ;
\n                      { line++; return BR; }
\'[^\n]*                return COMMENT;
(?i:rem)[\ \t]+[^\n]*   return COMMENT;
(?i:declare)    return DECLARE;
(?i:sub)        return SUB;
(?i:function)   return FUNCTION;
(?i:type)       return TYPE;
(?i:end)        return END;
(?i:dim)        return DIM;
(?i:shared)     return SHARED;
(?i:redim)      return REDIM;
(?i:static)     return STATIC;
(?i:let)        return LET;
(?i:const)      return CONST;
(?i:input)      return INPUT;
(?i:print)      return PRINT;
(?i:using)      return USING;
(?i:open)       return OPEN;
(?i:access)     return ACCESS;
(?i:read)       return READ;
(?i:write)      return WRITE;
(?i:close)      return CLOSE;
(?i:output)     return OUTPUT;
(?i:random)     return RANDOM;
(?i:binary)     return BINARY;
(?i:append)     return APPEND;
(?i:goto)       return GOTO;
(?i:gosub)      return GOSUB;
(?i:return)     return RETURN;
(?i:exit)       return EXIT;
(?i:if)         return IF;
(?i:then)       return THEN;
(?i:elseif)     return ELSEIF;
(?i:else)       return ELSE;
(?i:endif)      return ENDIF;
(?i:select)     return SELECT;
(?i:case)       return CASE;
(?i:for)        return FOR;
(?i:to)         return TO;
(?i:step)       return STEP;
(?i:next)       return NEXT;
(?i:while)      return WHILE;
(?i:wend)       return WEND;
(?i:do)         return DO;
(?i:loop)       return LOOP;
(?i:until)      return UNTIL;
(?i:as)         return AS;
(?i:bool)       return BOOL;
(?i:integer)    return INTEGER;
(?i:long)       return LONG;
(?i:single)     return SINGLE;
(?i:double)     return DOUBLE;
(?i:string)     return STRING;
[,;]                    return SEP;
(=|<|>|<=|>=|<>)        return BIN_EQU;
(?i:and|or|xor|imp|eqv) return BIN_LOG;
(?i:mod)                return BIN_ARI;
[\+\-]                  return BIN_ADD;
[\*\/\\]                return BIN_MUL;
[\^]                    return BIN_POW;
(?i:not)                return UNA_LOG;
(?i:true|false)         { yylval.b = strcmp(lower(yytext), "true")==0; return BOOL; }
{STR}                   return STRING;
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
