#include "parser.h"

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

int starts_with(const char *string, const char *substring) {
    while (*substring) {
        if (*substring++ != *string++) {
            return 1; // Substring does not match at the beginning
        }
    }
    return 0; // Substring matches at the beginning
}

HashTable parsefile(const char* filedata) {
    HashTable* AST = create_table();
    const char* lex = lexfile(filedata);

    if (filedata == NULL) {
        return *AST;
    }

    HashTable* declarations = create_table();
    HashTable* raw = create_table();

    // Parse the file
    if (lex == NULL) {
    return *AST;
    }

    while (lex != NULL) {
        if (starts_with(lex, "let") || starts_with(lex, "const") || starts_with(lex, "for") || starts_with(lex, "while")) {
            lex = lexfile(lex); // Move to the next token
            if (lex == NULL) {
                break;
            }

            char* name = lex; // Get the name
            lex = lexfile(lex); // Move to the next token
            if (lex == NULL) {
                break;
            }

            char* value = lex; // Get the value
            lex = lexfile(lex); // Move to the next token
            if (lex == NULL) {
                break;
            }

            // Insert name and value into the declarations and raw structures
            insert(declarations, name, value);
            insert(raw, name, value);
        } else if (
            strstr(lex, "+") || 
            strstr(lex, "-") ||
            strstr(lex, "*") || 
            strstr(lex, "/") || 
            strstr(lex, "%") ||
            strstr(lex, "^") ||
            strstr(lex, "=") ||
            strstr(lex, "<") ||
            strstr(lex, ">") ||
        ) {
            lex = lexfile(lex);
            if (lex == NULL) {
                break;
            }

            
        }
    }

    insert(AST, "declarations", to_json(declarations));
    insert(AST, "raw", to_json(raw));
    free_table(declarations);
    free_table(raw);
    free(lex);

    // Return the AST
    return *AST;
}