#include "parser.h"

struct parser {

};

cJSON* converter(const struct parser* AST) {
    cJSON* json = cJSON_CreateObject();
    if (json == NULL) {
        return NULL;
    }

    return json;
}

void out(const char* filename, const cJSON* data) {
    FILE *f = fopen(filename, "w");
    if (f == NULL) {
        return;
    }
    const char* json = cJSON_Print(data);
    if (json == NULL) {
        return;
    }
    fputs(json, f);
    fclose(f);
}

struct parser parsefile(const char* filedata) {
    struct parser AST;
    
    return AST;
}