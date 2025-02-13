%{
	#include<stdio.h>
	int charCount = 0, wordCount = 0, lineCount = 0;
%}
%option noyywrap
%%
.           { charCount++; }
\n          { charCount++; lineCount++; }
[ ]+  { charCount++; } 
[A-Za-z0-9]+ { wordCount++; charCount += yyleng; }
%%
void main()
{
	yylex();
	printf("Characters : %d\n", charCount);
	printf("Words : %d\n", wordCount);
	printf("Lines : %d\n", lineCount);
	exit(0);
}
