#ifndef HASH_TABLE_H
#define HASH_TABLE_H

#define TABLE_SIZE 100

typedef struct Entry {
    char* key;
    char* value;
    struct Entry* next;
} Entry;

typedef struct {
    Entry* entries[TABLE_SIZE];
} HashTable;

unsigned int hash(const char* key);
HashTable* create_table();
void free_table(HashTable* table);
void insert(HashTable* table, const char* key, const char* value);
char* search(HashTable* table, const char* key);
void delete(HashTable* table, const char* key);
void iterate(HashTable* table, void (*func)(const char*, const char*));
char* to_json(HashTable* table);

#endif // HASH_TABLE_H
