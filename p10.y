%{
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void yyerror(char *);
int yylex(void);
%}

%union {
    double dval;
}

%token <dval> DIGIT
%token EOL
%type <dval> E T F G

%left PLUS MINUS
%left TIMES DIVIDE
%right POWER
%left LPAREN RPAREN

%%
S : L
  | S L
  ;

L : E EOL { printf("Result: %.6f\n", $1); }
  | EOL   { /* Skip empty lines */ }
  ;

E : E PLUS T { $$ = $1 + $3; }
  | E MINUS T { $$ = $1 - $3; }
  | T { $$ = $1; }
  ;

T : T TIMES F { $$ = $1 * $3; }
  | T DIVIDE F { 
      if($3 == 0) {
          yyerror("Division by zero");
          exit(1);
      }
      $$ = $1 / $3; 
    }
  | F { $$ = $1; }
  ;

F : G POWER F { $$ = pow($1, $3); }
  | G { $$ = $1; }
  ;

G : LPAREN E RPAREN { $$ = $2; }
  | DIGIT { $$ = $1; }
  ;
%%

void yyerror(char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main() {
    printf("Enter an arithmetic expression and press Enter to calculate:\n");
    yyparse();
    return 0;
}