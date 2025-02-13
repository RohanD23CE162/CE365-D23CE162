%{
#include<stdio.h>
%}
%option noyywrap
%%
[0-9]+ {printf("%s\n",yytext);}
. ;
%%
void main()
{
yylex();
}
