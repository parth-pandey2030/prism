#include <stdio.h>
#include <stdlib.h>
 // This file is literally
 // just a testing file
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
    int *array = NULL;
    int size = 0;
    int capacity = 2;  // Initial capacity

    // Allocate initial memory
    array = (int *)malloc(capacity * sizeof(int));
    if (array == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    // Assume the array initially contains some values
    array[0] = 10;
    array[1] = 20;
    size = 2;

    // Example values to append
    int values_to_append[] = {30, 40, 50, 60};
    int num_values_to_append = sizeof(values_to_append) / sizeof(values_to_append[0]);

    for (int i = 0; i < num_values_to_append; i++) {
        appendValue(&array, &size, &capacity, values_to_append[i]);
    }

    // Print the array
    printf("Array elements: ");
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");

    // Free the allocated memory
    free(array);

    return 0;
}
