%{
    #include<stdio.h>
    #include<stdlib.h> 
    int yylex(void); /* Add this declaration */
    int yyerror(char *msg); /* Add this declaration */
%}

%token a b i t e NL 

%% 

stmt: S NL { printf("\n-> Valid string!\n"); exit(0); }
;
S: i E t S Sdash  
| a  
;
Sdash: e S 
| /* empty */ 
; 
E: b 
; 

%%

int yyerror(char *msg) 
{ 
    printf("\n-> Invalid string!!\n");  
    exit(0); 
} 

int main() 
{ 
    printf("Enter the string -> ");  
    yyparse(); 
    return 0; 
}