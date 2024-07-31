#include <stdio.h>
#include "hash_table.h"

int main() {
    HashTable* table = create_table();

    insert(table, "key1", "value1");
    insert(table, "key2", "value2");
    insert(table, "key3", "value3");

    printf("key1: %s\n", search(table, "key1"));
    printf("key2: %s\n", search(table, "key2"));
    printf("key3: %s\n", search(table, "key3"));

    delete(table, "key2");
    printf("key2: %s\n", search(table, "key2"));

    free_table(table);

    return 0;
}
