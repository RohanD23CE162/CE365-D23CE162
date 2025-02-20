%{
    #include <stdio.h>
    #include <string.h>
    void printToken(char* type, char* value);
%}

%option noyywrap

/* basic patterns */
digit    [0-9]
letter   [a-zA-Z]
id       {letter}({letter}|{digit})*
int      {digit}+
float    {digit}+"."{digit}+
ws       [ \t\r\f\v]+
char     \'[^\']\' 
string   \"[^\"]*\"

%%

    /* all C keywords */
"auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while"|"main" {
    printToken("Keyword", yytext);
}

{id} {
    printToken("Identifier", yytext);
}

{float} {
    printToken("Float", yytext);
}

{int} {
    printToken("Integer", yytext);
}

{char} {
    printToken("Character", yytext);
}

{string} {
    printToken("String", yytext);
}

    /* symbols */
[(){};,] {
    printToken("Symbol", yytext);
}

    /* operators */
[+\-*/=<>!] {
    printToken("Operator", yytext);
}

    /* skip comments */
"//".*  { }
"/*"([^*]|\*+[^*/])*\*+"/" { }

\n      { }
{ws}    { }

.       { printf("Error: Invalid character %s\n", yytext); }

%%

/* print token in a nice format */
void printToken(char* type, char* value) {
    printf("%s: %s\n", type, value);
}

int main() {
    yyin = fopen("input.c", "r");
    if(!yyin) {
        printf("Can't open input.c\n");
        return 1;
    }

    printf("Analyzing input.c...\n\n");
    yylex();
    fclose(yyin);
    return 0;
}
