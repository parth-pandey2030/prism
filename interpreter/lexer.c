#include "lexer.h"
#include <string.h>

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

// Structure to hold token definitions
typedef struct {
    char *name;
    regex_t regex;
} TokenDef;

// Define the lexer
char* lexfile(const char* filedata) {
    // Open the JSON file
    FILE *jsonfile = fopen("tokens.json", "r");
    if (jsonfile == NULL) {
        fprintf(stderr, "Failed to open tokens.json\n");
        exit(1);
    }

    // Read the JSON file content
    char container[457];
    if (fgets(container, sizeof(container), jsonfile) == NULL) {
        fprintf(stderr, "Failed to read tokens.json\n");
        fclose(jsonfile);
        exit(1);
    }
    fclose(jsonfile);

    // Parse the JSON
    cJSON *json = cJSON_Parse(container);
    if (json == NULL) {
        fprintf(stderr, "Failed to parse JSON\n");
        exit(1);
    }

    // Extract token definitions from JSON
    int token_count = cJSON_GetArraySize(json);
    TokenDef *token_defs = (TokenDef *)malloc(token_count * sizeof(TokenDef));
    if (token_defs == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < token_count; i++) {
        cJSON *token_json = cJSON_GetArrayItem(json, i);
        token_defs[i].name = cJSON_GetObjectItem(token_json, "name")->valuestring;
        const char *pattern = cJSON_GetObjectItem(token_json, "pattern")->valuestring;

        // Compile the regex
        if (regcomp(&token_defs[i].regex, pattern, REG_EXTENDED) != 0) {
            fprintf(stderr, "Failed to compile regex for token: %s\n", token_defs[i].name);
            exit(1);
        }
    }

    cJSON_Delete(json);

    // Tokenize the input file data
    int *tokens = NULL;
    int size = 0;
    int capacity = 2;  // Initial capacity
    tokens = (int *)malloc(capacity * sizeof(int));
    if (tokens == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }

    const char *cursor = filedata;
    while (*cursor != '\0') {
        int matched = 0;
        for (int i = 0; i < token_count; i++) {
            regmatch_t match;
            if (regexec(&token_defs[i].regex, cursor, 1, &match, 0) == 0 && match.rm_so == 0) {
                // We have a match
                int match_length = match.rm_eo;
                appendValue(&tokens, &size, &capacity, i);
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
            }
            free(token_defs);
            exit(1);
        }
    }

    // Create a string to return the tokens
    size_t output_size = 1024;
    char *output = (char *)malloc(output_size);
    if (output == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(1);
    }
    output[0] = '\0';

    for (int i = 0; i < size; i++) {
        const char *token_name = token_defs[tokens[i]].name;
        size_t needed_size = strlen(output) + strlen(token_name) + 2;
        if (needed_size > output_size) {
            output_size *= 2;
            char *new_output = (char *)realloc(output, output_size);
            if (new_output == NULL) {
                fprintf(stderr, "Memory reallocation failed\n");
                free(output);
                exit(1);
            }
            output = new_output;
        }
        strcat(output, token_name);
        strcat(output, " ");
    }

    // Clean up
    for (int i = 0; i < token_count; i++) {
        regfree(&token_defs[i].regex);
    }
    free(token_defs);
    free(tokens);

    return output;
}
