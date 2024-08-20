#include "executor.h"

// TODO - Handle "let" and "const" declarations

// Function to interpret and execute JSON-based code
void interpret_and_execute(const cJSON* json) {
    if (json == NULL) {
        printf("No JSON data to execute.\n");
        return;
    }

    cJSON* declarations = cJSON_GetObjectItem(json, "declarations");
    if (declarations == NULL) {
        printf("No declarations found.\n");
        return;
    }

    // Iterate over the declarations and execute them
    cJSON* declaration = NULL;
    cJSON_ArrayForEach(declaration, declarations) {
        const char* key = declaration->string;
        const char* value = declaration->valuestring;

        // Handle different types of declarations or operations
        if (starts_with(key, "let") || starts_with(key, "const")) {

        } else if (starts_with(key, "print")) {
            printf("%s\n", value);
        } else {
            printf("Unknown declaration: %s = %s\n", key, value);
        }
    }
}

// Function to execute a line of code
void execute_line(const char* code_line) {
    if (code_line == NULL || strlen(code_line) == 0) {
        printf("No code to execute.\n");
        return;
    }

    // Parse the code line and create an AST
    HashTable* AST = parsefile(code_line);
    if (AST == NULL) {
        printf("Failed to parse the code.\n");
        return;
    }

    // Convert the AST to JSON
    cJSON* json = converter(AST);
    if (json == NULL) {
        printf("Failed to convert AST to JSON.\n");
        free_table(AST);
        return;
    }

    // Print the JSON representation of the AST
    char* json_string = cJSON_Print(json);
    if (json_string == NULL) {
        printf("Failed to print JSON.\n");
        cJSON_Delete(json);
        free_table(AST);
        return;
    }

    printf("JSON Output: %s\n", json_string);

    // Interpret and execute the JSON-based code
    interpret_and_execute(json);

    // Clean up
    free(json_string);
    cJSON_Delete(json);
    free_table(AST);
}

// Function to execute the whole code
void execute(const char* code) {
    if (code == NULL || strlen(code) == 0) {
        return;
    }
    int line_number = 0;
    char *line = strtok(code, "\n");

    while (line != NULL) {
        line_number++;
        execute_line(line);
        line = strtok(NULL, "\n");
    }
}