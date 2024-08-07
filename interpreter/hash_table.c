#include "hash_table.h"

// Simple hash function
unsigned int hash(const char* key) {
    unsigned long int value = 0;
    unsigned int i = 0;
    unsigned int key_len = strlen(key);

    // Compute the hash value
    for (; i < key_len; ++i) {
        value = value * 37 + key[i];
    }
    return value % TABLE_SIZE;
}

// Create a new hash table
HashTable* create_table() {
    HashTable* table = malloc(sizeof(HashTable));
    for (int i = 0; i < TABLE_SIZE; ++i) {
        table->entries[i] = NULL;
    }
    return table;
}

// Free the hash table
void free_table(HashTable* table) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Entry* entry = table->entries[i];
        while (entry != NULL) {
            Entry* tmp = entry;
            entry = entry->next;
            free(tmp->key);
            free(tmp->value);
            free(tmp);
        }
    }
    free(table);
}

// Insert a key-value pair into the hash table
void insert(HashTable* table, const char* key, const char* value) {
    unsigned int slot = hash(key);
    Entry* entry = table->entries[slot];

    // Check if the key already exists
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            // Update the value if the key already exists
            free(entry->value);
            entry->value = strdup(value);
            return;
        }
        entry = entry->next;
    }

    // Create a new entry
    entry = malloc(sizeof(Entry));
    entry->key = strdup(key);
    entry->value = strdup(value);
    entry->next = table->entries[slot];
    table->entries[slot] = entry;
}

// Search for a key in the hash table
char* search(HashTable* table, const char* key) {
    unsigned int slot = hash(key);
    Entry* entry = table->entries[slot];

    // Traverse the linked list
    while (entry != NULL) {
        if (strcmp(entry->key, key) == 0) {
            return entry->value;
        }
        entry = entry->next;
    }
    return NULL;
}

// Delete a key-value pair from the hash table
void delete(HashTable* table, const char* key) {
    unsigned int slot = hash(key);
    Entry* entry = table->entries[slot];
    Entry* prev = NULL;

    // Traverse the linked list
    while (entry != NULL && strcmp(entry->key, key) != 0) {
        prev = entry;
        entry = entry->next;
    }

    if (entry == NULL) {
        // Key not found
        return;
    }

    if (prev == NULL) {
        // Remove the first entry in the linked list
        table->entries[slot] = entry->next;
    } else {
        // Remove the entry from the linked list
        prev->next = entry->next;
    }

    free(entry->key);
    free(entry->value);
    free(entry);
}

// Iterate over all key-value pairs in the hash table
void iterate(HashTable* table, void (*func)(const char*, const char*)) {
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Entry* entry = table->entries[i];
        while (entry != NULL) {
            func(entry->key, entry->value);
            entry = entry->next;
        }
    }
}

// Convert hash table to JSON string
char* to_json(HashTable* table) {
    cJSON* json = cJSON_CreateObject();
    for (int i = 0; i < TABLE_SIZE; ++i) {
        Entry* entry = table->entries[i];
        while (entry != NULL) {
            cJSON_AddStringToObject(json, entry->key, entry->value);
            entry = entry->next;
        }
    }
    char* json_string = cJSON_Print(json);
    cJSON_Delete(json);
    return json_string;
}

// Convert JSON string to HashTable
HashTable* from_json(const char* json_string) {
    // Parse the JSON string
    cJSON* json = cJSON_Parse(json_string);
    if (json == NULL) {
        fprintf(stderr, "Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        return NULL;
    }

    // Create a new hash table
    HashTable* table = create_table();

    // Iterate over all key-value pairs in the JSON object
    cJSON* current_element = NULL;
    cJSON_ArrayForEach(current_element, json) {
        const char* key = current_element->string;
        const char* value = cJSON_GetStringValue(current_element);
        
        if (key != NULL && value != NULL) {
            insert(table, key, value);
        }
    }

    // Clean up and return the hash table
    cJSON_Delete(json);
    return table;
}