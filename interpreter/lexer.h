#ifndef LEXER_H
#define LEXER_H

#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"


// Function to append a value to a dynamic array
void appendValue(int **array, int *size, int *capacity, int value);

// Function to perform lexical analysis
char* lexfile(const char* filedata);

#endif // LEXER_H

