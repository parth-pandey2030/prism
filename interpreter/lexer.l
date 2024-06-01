%{
    #include <stdio.h>
    #include <tokens.h>
    char tokens = {};

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
