%{
    #include <stdio.h>
    #include <string.h>
    
    void print_token(char* token_type, char* token_value);
%}

%option noyywrap

DIGIT       [0-9]
LETTER      [a-zA-Z]
ID          {LETTER}({LETTER}|{DIGIT})*
INT_CONST   {DIGIT}+
FLOAT_CONST {DIGIT}+"."{DIGIT}+
WHITESPACE  [ \t\r\f\v]+
CHAR_CONST  \'[^\']\' 
STR_CONST   \"[^\"]*\"

%%

"auto"|"break"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while" {
    print_token("Keyword", yytext);
}

{ID} {
    print_token("Identifier", yytext);
}

{FLOAT_CONST} {
    print_token("Float Constant", yytext);
}

{INT_CONST} {
    print_token("Integer Constant", yytext);
}

{CHAR_CONST} {
    print_token("Char Constant", yytext);
}

{STR_CONST} {
    print_token("String Constant", yytext);
}

"["|"]"|"("|")"|"{"|"}"|","|";"|":" {
    print_token("Punctuation", yytext);
}

"+"|"-"|"*"|"/"|"%"|"="|"<"|">"|"!"|"&"|"|"|"^"|"~"|"?"|"+="|"-="|"*="|"/="|"%="|"=="|"!="|"<="|">="|"&&"|"||"|"++"|"--" {
    print_token("Operator", yytext);
}

"//"[^\n]* { /* Single line comment - ignore */ }

"/*"([^*]|\*+[^*/])*\*+"/" { /* Multi-line comment - ignore */ }

\n { /* Ignore newlines */ }

{WHITESPACE} { /* Ignore whitespace */ }

. {
    printf("Lexical Error: Unexpected character '%s' at line %d\n", yytext, yylineno);
}

%%

void print_token(char* token_type, char* token_value) {
    printf("%-12s: %s\n", token_type, token_value);
}

int main() {
    FILE* input_file = fopen("input.c", "r");
    if (!input_file) {
        printf("Error: Cannot open input.c\n");
        return 1;
    }

    yyin = input_file;
    printf("\nTOKENS:\n");
    yylex();
    
    fclose(input_file);
    return 0;
}
