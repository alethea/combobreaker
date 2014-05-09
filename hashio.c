#include <stdlib.h>
#include <stdio.h>
#include "hash.h"

char nibble_to_hex(char nibble) {
    unsigned char c;

    c = nibble & 0x0f;
    if (c < 10) {
        return '0' + c;
    } else {
        return 'a' - 10 + c;
    }
}

void print_hash(const char *hash, size_t length) {
    size_t i;

    for (i = 0; i < length; i++) {
        putchar(nibble_to_hex(hash[i] >> 4));
        putchar(nibble_to_hex(hash[i]));
    }
    putchar('\n');
}
