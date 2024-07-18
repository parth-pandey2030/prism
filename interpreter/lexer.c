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

// Read the entire file content into a dynamically allocated string
char* readFile(const char* filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open %s\n", filename);
        exit(1);
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char *content = (char *)malloc(length + 1);
    if (content == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        exit(1);
    }

    fread(content, 1, length, file);
    content[length] = '\0';

    fclose(file);
    return content;
}

// Define the lexer
char* lexfile(const char* filedata) {
    // Read the JSON file content
    char *json_content = readFile("tokens.json");

    // Parse the JSON
    cJSON *json = cJSON_Parse(json_content);
    if (json == NULL) {
        fprintf(stderr, "Failed to parse JSON\n");
        free(json_content);
        exit(1);
    }
    free(json_content);

    // Extract token definitions from JSON
    int token_count = cJSON_GetArraySize(json);
    TokenDef *token_defs = (TokenDef *)malloc(token_count * sizeof(TokenDef));
    if (token_defs == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        cJSON_Delete(json);
        exit(1);
    }

    for (int i = 0; i < token_count; i++) {
        cJSON *token_json = cJSON_GetArrayItem(json, i);
        token_defs[i].name = strdup(cJSON_GetObjectItem(token_json, "name")->valuestring);
        const char *pattern = cJSON_GetObjectItem(token_json, "pattern")->valuestring;

        // Compile the regex
        if (regcomp(&token_defs[i].regex, pattern, REG_EXTENDED) != 0) {
            fprintf(stderr, "Failed to compile regex for token: %s\n", token_defs[i].name);
            for (int j = 0; j <= i; j++) {
                regfree(&token_defs[j].regex);
                free(token_defs[j].name);
            }
            free(token_defs);
            cJSON_Delete(json);
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
        for (int i = 0; i < token_count; i++) {
            regfree(&token_defs[i].regex);
            free(token_defs[i].name);
        }
        free(token_defs);
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
                free(token_defs[i].name);
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
        for (int i = 0; i < token_count; i++) {
            regfree(&token_defs[i].regex);
            free(token_defs[i].name);
        }
        free(tokens);
        free(token_defs);
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
                for (int j = 0; j < token_count; j++) {
                    regfree(&token_defs[j].regex);
                    free(token_defs[j].name);
                }
                free(tokens);
                free(token_defs);
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
        free(token_defs[i].name);
    }
    free(token_defs);
    free(tokens);

    return output;
}
