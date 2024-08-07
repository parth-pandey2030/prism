#include "lexer.h"
#include "tokens.h"
#include <string.h>
#include <regex.h>

// Append a value to an array
void appendValue(int **array, int *size, int *capacity, int value) {
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
    (*array)[*size] = value;
    (*size)++;
}

// Token definitions
typedef struct {
    char *name;
    regex_t regex;
} TokenDef;

static const char *token_names[] = {
    TOKEN_IDENTIFIER,
    TOKEN_LET,
    TOKEN_CONST,
    TOKEN_INT,
    TOKEN_FLOAT,
    TOKEN_IRRATIONAL,
    TOKEN_BOOLEAN,
    TOKEN_COMPLEX,
    TOKEN_STRING,
    TOKEN_ARRAY,
    TOKEN_SET,
    TOKEN_HASH,
    TOKEN_OPERATOR,
    TOKEN_PUNCTUATION,
    TOKEN_FOR_LOOP,
    TOKEN_WHILE_LOOP,
    TOKEN_FINISHED_LOOP,
    TOKEN_CONTINUE_LOOP,
    TOKEN_BREAK_LOOP,
    TOKEN_COMMENT,
    TOKEN_WHITESPACE,
    TOKEN_NEW_LINE,
    TOKEN_INFINITY,
    TOKEN_NULL,
    TOKEN_UNDEFINED,
    TOKEN_NAN,
    TOKEN_FUNCTION,
    TOKEN_RETURN,
    TOKEN_PRINT
};

static const char *token_patterns[] = {
    PATTERN_IDENTIFIER,
    PATTERN_LET,
    PATTERN_CONST,
    PATTERN_INT,
    PATTERN_FLOAT,
    PATTERN_IRRATIONAL,
    PATTERN_BOOLEAN,
    PATTERN_COMPLEX,
    PATTERN_STRING,
    PATTERN_ARRAY,
    PATTERN_SET,
    PATTERN_HASH,
    PATTERN_OPERATOR_COMPOUND,
    PATTERN_OPERATOR_SINGLE,
    PATTERN_PUNCTUATION,
    PATTERN_FOR_LOOP,
    PATTERN_WHILE_LOOP,
    PATTERN_FINISHED_LOOP,
    PATTERN_CONTINUE_LOOP,
    PATTERN_BREAK_LOOP,
    PATTERN_COMMENT,
    PATTERN_WHITESPACE,
    PATTERN_NEW_LINE,
    PATTERN_INFINITY,
    PATTERN_NULL,
    PATTERN_UNDEFINED,
    PATTERN_NAN,
    PATTERN_FUNCTION,
    PATTERN_RETURN,
    PATTERN_PRINT
};

// Define the lexer
char* lexfile(const char* filedata) {
    int token_count = sizeof(token_names) / sizeof(token_names[0]);
    TokenDef *token_defs = (TokenDef *)malloc(token_count * sizeof(TokenDef));
    if (token_defs == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < token_count; i++) {
        token_defs[i].name = strdup(token_names[i]);

        // Compile the regex
        if (regcomp(&token_defs[i].regex, token_patterns[i], REG_EXTENDED) != 0) {
            fprintf(stderr, "Failed to compile regex for token: %s\n", token_defs[i].name);
            for (int j = 0; j <= i; j++) {
                regfree(&token_defs[j].regex);
                free(token_defs[j].name);
            }
            free(token_defs);
            exit(1);
        }
    }

    // Tokenize the input file data
    int *tokens = NULL;
    int size = 0;
    int capacity = 2;  // Initial capacity
    tokens = (int *)malloc(capacity * sizeof(int));
    if (tokens == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        for (int i = 0; i < token_count; i++) {
            regfree(&token_defs[i].regex);
            free(token_defs[i].name);
        }
        free(token_defs);
        exit(1);
    }

    const char *cursor = filedata;
    char **matched_pieces = NULL;
    int matched_size = 0;
    int matched_capacity = 2;  // Initial capacity
    matched_pieces = (char **)malloc(matched_capacity * sizeof(char *));
    if (matched_pieces == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        for (int i = 0; i < token_count; i++) {
            regfree(&token_defs[i].regex);
            free(token_defs[i].name);
        }
        free(token_defs);
        free(tokens);
        exit(1);
    }

    while (*cursor != '\0') {
        int matched = 0;
        for (int i = 0; i < token_count; i++) {
            regmatch_t match;
            if (regexec(&token_defs[i].regex, cursor, 1, &match, 0) == 0 && match.rm_so == 0) {
                // We have a match
                int match_length = match.rm_eo;
                appendValue(&tokens, &size, &capacity, i);

                // Store the matched piece of code
                char *piece = strndup(cursor, match_length);
                if (matched_size >= matched_capacity) {
                    matched_capacity *= 2;
                    matched_pieces = (char **)realloc(matched_pieces, matched_capacity * sizeof(char *));
                    if (matched_pieces == NULL) {
                        fprintf(stderr, "Memory reallocation failed\n");
                        free(tokens);
                        for (int j = 0; j < token_count; j++) {
                            regfree(&token_defs[j].regex);
                            free(token_defs[j].name);
                        }
                        free(token_defs);
                        exit(1);
                    }
                }
                matched_pieces[matched_size++] = piece;

                cursor += match_length;
                matched = 1;
                break;
            }
        }

        if (!matched) {
            fprintf(stderr, "Unexpected character: %c\n", *cursor);
            free(tokens);
            for (int i = 0; i < token_count; i++) {
                regfree(&token_defs[i].regex);
                free(token_defs[i].name);
            }
            free(token_defs);
            for (int i = 0; i < matched_size; i++) {
                free(matched_pieces[i]);
            }
            free(matched_pieces);
            exit(1);
        }
    }

    // Create a string to return the tokens and their matched pieces
    size_t output_size = 1024;
    char *output = (char *)malloc(output_size);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        for (int i = 0; i < token_count; i++) {
            regfree(&token_defs[i].regex);
            free(token_defs[i].name);
        }
        free(tokens);
        free(token_defs);
        for (int i = 0; i < matched_size; i++) {
            free(matched_pieces[i]);
        }
        free(matched_pieces);
        exit(1);
    }
    output[0] = '\0';

    for (int i = 0; i < size; i++) {
        const char *token_name = token_defs[tokens[i]].name;
        const char *matched_piece = matched_pieces[i];
        size_t needed_size = strlen(output) + strlen(token_name) + strlen(matched_piece) + 4;
        if (needed_size > output_size) {
            output_size *= 2;
            char *new_output = (char *)realloc(output, output_size);
            if (new_output == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                for (int j = 0; j < token_count; j++) {
                    regfree(&token_defs[j].regex);
                    free(token_defs[j].name);
                }
                free(tokens);
                free(token_defs);
                free(output);
                for (int i = 0; i < matched_size; i++) {
                    free(matched_pieces[i]);
                }
                free(matched_pieces);
                exit(1);
            }
            output = new_output;
        }
        strcat(output, token_name);
        strcat(output, ":");
        strcat(output, matched_piece);
        strcat(output, " ");
    }

    // Clean up
    for (int i = 0; i < token_count; i++) {
        regfree(&token_defs[i].regex);
        free(token_defs[i].name);
    }
    free(token_defs);
    free(tokens);
    for (int i = 0; i < matched_size; i++) {
        free(matched_pieces[i]);
    }
    free(matched_pieces);

    return output;
}
