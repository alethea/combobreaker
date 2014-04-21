#include <stdio.h>
#include <stdlib.h>
#include "loader.h"

int main() {
    char *data;
    size_t length;
    
    load("main.c", &data, &length);
    printf("%s\n%d\n", data, (int)length);
    return EXIT_SUCCESS;
}
