#include <stdio.h>
#include <stdlib.h>
#include "loader.h"
#include "hash.h"

int main() {
    char *data;
    size_t length;
    char *digest;
    int i;
    
    load("main.c", &data, &length);
    digest = sha256(data, length);

    printf("main.c: ");
    for (i = 0; i < SHA256_LENGTH; i++) {
        printf("%02hhx", digest[i]);
    }
    printf("\n");

    return 0;
}
