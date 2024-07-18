#include "lexer.h"
#include <stdio.h>

int main() {
    char *tokens = lexfile("0+1");
    if (tokens) {
        printf("%s\n", tokens);
        free(tokens);  // Free the allocated memory for tokens
    }
    return 0;
}

