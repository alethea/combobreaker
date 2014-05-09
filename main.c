#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"

int main() {
    char *test;
    char *ref;
    int match;

    test = sha256("hello", 5);
    ref = scan_hash(SHA256_LENGTH);

    match = memcmp(test, ref, SHA256_LENGTH);

    free(ref);
    free(test);
    if (match) {
        return 1;
    }
    return 0;
}
