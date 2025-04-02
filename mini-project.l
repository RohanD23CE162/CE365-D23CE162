%{
#include <stdio.h>
#include <string.h>

int line_number = 1;
int brace_count = 0;
int semicolon_count = 0;
int in_for_loop = 0;
int has_condition = 0;
int has_init = 0;
int has_update = 0;
%}

%%
"for"                     { 
                            in_for_loop = 1;
                            semicolon_count = 0;
                            has_condition = 0;
                            has_init = 0;
                            has_update = 0;
                          }
"("                       { 
                            if (in_for_loop) {
                                // Just track, no print
                            }
                          }
")"                       { 
                            if (in_for_loop) {
                                if (semicolon_count != 2) {
                                    printf("Error at line %d: For loop must have exactly 2 semicolons\n", line_number);
                                    if (semicolon_count == 0) {
                                        printf("Error at line %d: Missing initialization and condition\n", line_number);
                                    } else if (semicolon_count == 1) {
                                        printf("Error at line %d: Missing condition\n", line_number);
                                    }
                                }
                                if (!has_init) {
                                    printf("Error at line %d: Missing initialization expression\n", line_number);
                                }
                                if (!has_condition) {
                                    printf("Error at line %d: Missing condition\n", line_number);
                                }
                                if (!has_update) {
                                    printf("Error at line %d: Missing update expression\n", line_number);
                                }
                                in_for_loop = 0;
                            }
                          }
";"                       { 
                            if (in_for_loop) {
                                semicolon_count++;
                                if (semicolon_count == 1 && !has_init) {
                                    printf("Error at line %d: Missing initialization expression\n", line_number);
                                }
                                if (semicolon_count == 2 && !has_condition) {
                                    printf("Error at line %d: Missing condition\n", line_number);
                                }
                            }
                          }
"{"                       { 
                            if (in_for_loop) {
                                brace_count++;
                            }
                          }
"}"                       { 
                            if (in_for_loop) {
                                brace_count--;
                                if (brace_count < 0) {
                                    printf("Error at line %d: Extra closing brace\n", line_number);
                                }
                            }
                          }

[0-9]+                    { 
                            if (in_for_loop) {
                                if (semicolon_count == 0) has_init = 1;
                                else if (semicolon_count == 1) has_condition = 1;
                                else if (semicolon_count == 2) has_update = 1;
                            }
                          }
[a-zA-Z_][a-zA-Z0-9_]*   { 
                            if (in_for_loop) {
                                if (semicolon_count == 0) has_init = 1;
                                else if (semicolon_count == 1) has_condition = 1;
                                else if (semicolon_count == 2) has_update = 1;
                            }
                          }

[+\-*/=<>!%]             { 
                            if (in_for_loop) {
                                // Valid operators in for loop
                            }
                          }
[\"']                     { 
                            if (in_for_loop) {
                                // Valid string delimiters
                            }
                          }
[\\]                      { 
                            if (in_for_loop) {
                                // Valid escape character
                            }
                          }

[ \t]                     ; /* Skip whitespace */
\n                        { line_number++; }
"//".*                    ; /* Skip single-line comments */
"/*"([^*]|\*+[^*/])*\*+"/" ; /* Skip multi-line comments */

.                         { 
                            if (in_for_loop) {
                                printf("Error at line %d: Unexpected character '%s'\n", line_number, yytext);
                            }
                          }

%%

int yywrap() {
    if (brace_count > 0) {
        printf("Error: Unclosed braces at end of file\n");
    }
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <c_file>\n", argv[0]);
        return 1;
    }

    FILE *input = fopen(argv[1], "r");
    if (!input) {
        fprintf(stderr, "Error: Cannot open file %s\n", argv[1]);
        return 1;
    }

    yyin = input;
    printf("Analyzing C for loops in file: %s\n", argv[1]);
    printf("----------------------------------------\n");
    
    yylex();
    
    printf("----------------------------------------\n");
    printf("Analysis complete.\n");
    
    fclose(input);
    return 0;
} 