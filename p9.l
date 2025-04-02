%option noyywrap
%{
    #include<stdio.h>
    #include "y.tab.h"  /* Changed from PRACTICAL_9.tab.h to y.tab.h */
%}

%%

[i] {return i;}
[t] {return t;} 
[a] {return a;} 
[b] {return b;} 
[e] {return e;} 
\n {return NL;} 
. {return yytext[0];} 

%%

/* Remove the yywrap function since we're using %option noyywrap */