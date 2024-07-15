#include <stdio.h>
#include <stdlib.h>
#include "cJSON.h"

int main() {
    // Create JSON object
    cJSON *json = cJSON_CreateObject();

    // Add items to JSON object
    cJSON_AddStringToObject(json, "name", "John");
    cJSON_AddNumberToObject(json, "age", 30);
    cJSON_AddStringToObject(json, "city", "New York");

    // Print JSON string
    char *json_string = cJSON_Print(json);
    printf("%s\n", json_string);

    // Free JSON string and object
    free(json_string);
    cJSON_Delete(json);
    return 0;
}
