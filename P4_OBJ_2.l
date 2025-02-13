%{
#include<stdio.h>
%}
%option noyywrap
%%
(charusat) {printf("university");}
%%
void main()
{
yylex();
}
