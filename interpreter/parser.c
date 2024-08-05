#include "parser.h"

// Utility function to create JSON object from a hash table
cJSON* converter(const HashTable* AST) {
    if (AST == NULL) {
        return NULL;
    }

    cJSON* json = cJSON_CreateObject();
    if (json == NULL) {
        return NULL;
    }

    for (int i = 0; i < TABLE_SIZE; ++i) {
        Entry* entry = AST->entries[i];
        while (entry != NULL) {
            cJSON_AddStringToObject(json, entry->key, entry->value);
            entry = entry->next;
        }
    }

    return json;
}

// Function to write JSON data to a file
void out(const char* filename, const cJSON* data) {
    if (data == NULL || filename == NULL) {
        return;
    }

    FILE* f = fopen(filename, "w");
    if (f == NULL) {
        return;
    }

    char* json_string = cJSON_Print(data);
    if (json_string == NULL) {
        fclose(f);
        return;
    }

    fputs(json_string, f);
    fclose(f);
    free(json_string);
}

// Function to check if a string starts with a substring
int starts_with(const char *string, const char *substring) {
    while (*substring) {
        if (*substring++ != *string++) {
            return 0; // Substring does not match at the beginning
        }
    }
    return 1; // Substring matches at the beginning
}

// Function to parse file data and create an AST
HashTable* parsefile(const char* filedata) {
    HashTable* AST = create_table();
    if (filedata == NULL) {
        return AST;
    }

    const char* lex = lexfile(filedata);
    if (lex == NULL) {
        return AST;
    }

    HashTable* declarations = create_table();
    HashTable* raw = create_table();
    HashTable* init = create_table();

    while (lex != NULL) {
        if (
            strstr(lex, "let") || 
            strstr(lex, "const") || 
            strstr(lex, "for") || 
            strstr(lex, "while")
        ) {
            lex = lexfile(lex);
            if (lex == NULL) {
                break;
            }

            char* name = strdup(lex);
            lex = lexfile(lex);
            if (lex == NULL) {
                break;
            }

            char* value = strdup(lex);
            lex = lexfile(lex);
            if (lex == NULL) {
                break;
            }

            insert(declarations, name, value);
        } else if (
            strstr(lex, "+") || 
            strstr(lex, "-") ||
            strstr(lex, "*") || 
            strstr(lex, "/") || 
            strstr(lex, "%") ||
            strstr(lex, "^") ||
            strstr(lex, "=") ||
            strstr(lex, "<") ||
            strstr(lex, ">")
        ) {
            lex = lexfile(lex);
            if (lex == NULL) {
                break;
            }

            char* left = strdup(lex);
            lex = lexfile(lex);
            if (lex == NULL) {
                break;
            }

            char* right = strdup(lex);
            lex = lexfile(lex);
            if (lex == NULL) {
                break;
            }

            insert(init, left, right);
        } else if (
            strstr(lex, "and") ||
            strstr(lex, "or") ||
            strstr(lex, "not")
        ) {
            lex = lexfile(lex);
            if (lex == NULL) {
                break;
            }

            char* left = strdup(lex);
            lex = lexfile(lex);
            if (lex == NULL) {
                break;
            }

            char* right = strdup(lex);
            lex = lexfile(lex);
            if (lex == NULL) {
                break;
            }

            insert(init, left, right);
        } else if (
            strstr(lex, "int") || 
            strstr(lex, "float") || 
            strstr(lex, "string") ||
            strstr(lex, "bool") ||
            strstr(lex, "irrational") ||
            strstr(lex, "complex") ||
            strstr(lex, "array") ||
            strstr(lex, "set") ||
            strstr(lex, "infinity") ||
            strstr(lex, "nan") ||
            strstr(lex, "null") ||
            strstr(lex, "undefined") ||
            strstr(lex, "function")
        ) {
            char* before = strdup(lex);
            lex = lexfile(lex);
            if (lex == NULL) {
                break;
            }
            if (before == NULL) {
                insert(raw, before, before);
            } else {
                insert(init, before, strdup(lex));
            }
        } else if (strstr(lex, "punctuation")) {
            lex = lexfile(lex);
            if (lex == NULL) {
                break;
            }
        } else {
            break;
        }
    }

    insert(declarations, "init", to_json(init));
    insert(AST, "declarations", to_json(declarations));
    insert(AST, "raw", to_json(raw));

    free_table(declarations);
    free_table(raw);
    free_table(init);

    return AST;
}
