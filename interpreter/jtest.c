#include <stdio.h>
#include "cJSON.h"

int main() {
    FILE *jsonfile = fopen("tokens.json", "r");
    char container[457];
    fgets(container, 457, jsonfile);
    cJSON *json = cJSON_Parse(container);
    printf("%s", cJSON_Print(json));
    return 0;
}