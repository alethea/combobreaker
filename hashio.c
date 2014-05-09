#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <error.h>
#include "hash.h"

char nibble_to_hex(char nibble) {
    unsigned char c;

    c = (unsigned) nibble & 0x0f;
    if (c < 10) {
        return '0' + c;
    } else {
        return 'a' - 10 + c;
    }
}

unsigned char hex_to_nibble(char hex) {
    if (hex >= '0' && hex <= '9') {
        return hex - '0';
    } else if (hex >= 'a' && hex <= 'f') {
        return hex - 'a' + 10;
    } else if (hex >= 'A' && hex <= 'F') {
        return hex - 'A' + 10;
    } else {
        error(-1, 0, "'%c' out of range", hex);
        return 0;
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

char *scan_hash(size_t length) {
    size_t i;
    char *buf;
    
    
    buf = calloc(length, sizeof (char));
    if (buf == NULL) {
        error(-1, errno, "Cannot read input hash");
    }
    for (i = 0; i < length; i++) {
        buf[i] = hex_to_nibble(getchar()) << 4;
        buf[i] |= hex_to_nibble(getchar());
    }
    return buf;
}
