#include <stdio.h>
#include <stdlib.h>
#include "hash.h"

int main() {
    char *hash;
    int i;
    
    hash = sha256("abc", 3);

    printf("main.c: ");
    for (i = 0; i < SHA256_LENGTH; i++) {
        printf("%02hhx", hash[i]);
    }
    printf("\n");

    free(hash);
    return 0;
}
