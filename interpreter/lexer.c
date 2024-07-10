#include <stdio.h>
#include <stdlib.h>

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

int main() {
    
}