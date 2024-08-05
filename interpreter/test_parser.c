#include "parser.h"

int main() {
    HashTable* table = parsefile("hello");
    if (table == NULL) {
        return 1;
    }

    cJSON* json = converter(table);
    if (json == NULL) {
        return 1;
    }

    out("hello_parsed.json", json);
    return 0;
}
