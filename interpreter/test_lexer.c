#include "lexer.h"
#include <stdio.h>

int main() {
    char *tokens = lexfile("01");
    if (tokens) {
        printf("%s\n", tokens);
        free(tokens);  // Free the allocated memory for tokens
    }
    return 0;
}
