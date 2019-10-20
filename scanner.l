%{
#include "parser.tab.h"
int line = 0;
%}

%% 

[ \t]         ;
\n            { line++; return '\n'; }
[0-9][0-9]*   { return INTEGER; }
\+            { return PLUS; }

%%
