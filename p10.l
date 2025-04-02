%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "practical-10.tab.h"

void yyerror(char *);
%}

%%
[0-9]+      { yylval.dval = atof(yytext); return DIGIT; }
[0-9]+\.[0-9]+ { yylval.dval = atof(yytext); return DIGIT; }
"+"         { return PLUS; }
"-"         { return MINUS; }
"*"         { return TIMES; }
"/"         { return DIVIDE; }
"^"         { return POWER; }
"("         { return LPAREN; }
")"         { return RPAREN; }
[\n]        { return EOL; }  /* Return EOL token on newline */
[ \t]       ; /* Skip other whitespace */
.           { yyerror("Invalid character"); }
%%

int yywrap(void) {
    return 1;
}