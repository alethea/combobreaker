#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

int main() {
    char *hash;

    hash = sha256("hello", 5);
    print_hash(hash, SHA256_LENGTH);

    free(hash);
    return 0;
}
