%{
    #include <stdio.h>
    #include <stdlib.h>
    int lower = 0, upper = 0, digit = 0, special = 0, length = 0;
%}

%option noyywrap

%%
[a-z]     { lower = 1; length++; }
[A-Z]     { upper = 1; length++; }
[0-9]     { digit = 1; length++; }
[*;#$@]   { special = 1; length++; }
.         { length++; }  // Count any other character
\n        { 
             if (length >= 9 && length <= 15 && lower && upper && digit && special)
                 printf("Valid password\n");
             else
                 printf("Invalid password\n");
             
             lower = upper = digit = special = length = 0;
          }
%%

int main() {
    printf("Enter password: ");
    yylex();
    return 0;
}

