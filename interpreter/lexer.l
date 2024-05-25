%{
    #include <stdio.h>
    char tokens = {};

    const char INT[] = "INT";
    const char FLOAT[] = "FLOAT";
    const char PLUS[] = "PLUS";
    const char MINUS[] = MINUS;
    const char MUL[] = "MUL";
    const char DIV[] = "DIV";
    const char LPAREN[] = "LPAREN";
    const char RPAREN[] = "RPAREN";
    const char IDENTIFIER[] = "IDENTIFIER";
    const char COMMENT[] = "COMMENT";
    const char DIGITS[] = "0123456789";

    void appendToken(int **array, int *size, int *capacity, int value) {

        // Check if we need to resize the array
        if (*size >= *capacity) {
            *capacity *= 2;  // Double the capacity
            int *new_array = (int *)realloc(*array, *capacity * sizeof(int));
            if (new_array == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(*array);
                exit(1);
            }
            *array = new_array;
        }

        // Append the new value
        (*array)[*size] = value;
        (*size)++;
    }
    int size = sizeof(tokens);
    int capacity = size + 2;
%}
%%
[0-9+] {appendToken(&tokens, &size, &capacity, INT)} // Integers
[0-9]+\.[0-9]+ {appendToken(&tokens, &size, &capacity, FLOAT)} // Floating point numbers
[0-9]+\.[0-9]* {appendToken(&tokens, &size, &capacity, FLOAT)}
\.[0-9]+ {appendToken(&tokens, &size, &capacity, FLOAT)}

%%

int yywrap() { }
int main() {
    yylex();

    return 0;
}