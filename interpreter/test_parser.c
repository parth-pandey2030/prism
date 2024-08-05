#include "parser.h"

int main() {
    HashTable* table = parsefile("filedata");
    if (table == NULL) {
        return 1;
    }

    cJSON* json = converter(table);
    if (json == NULL) {
        return 1;
    }

    out("output_name.json", json);
    return 0;
}
