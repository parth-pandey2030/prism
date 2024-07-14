#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

FILE *jsonfile = fopen("tokens.json", "r");
char container[457];

void appendValue(int **array, int *size, int *capacity, int value) {
    // Check if we need to resize the array
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

    // Append the new value
    (*array)[*size] = value;
    (*size)++;
}

char* lexfile(char* filedata) {
     char* tokens = {};
     int size = 0;
     int capacity = 2;  // Initial capacity
     fgets(container, 457, jsonfile); // Read the tokens file
     cJSON *json = cJSON_Parse(container);
     
}