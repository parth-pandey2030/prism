#include <stdio.h>
#include <stdlib.h>

void colorText(char* text) {
    printf("\033[0;31m");
    printf(text);
}
