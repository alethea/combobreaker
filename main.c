#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include "hash.h"
#include "alphabet.h"

int main() {
    char *test;
    char *ref;
    int match;
    unsigned long count;
    alphabet_iter *iter;

    match = 1;
    count = 0;
    iter = make_alphabet_iter(8);
    ref = scan_hash(SHA256_LENGTH);

    while (match) {
        alphabet_next(iter);
        test = sha256(iter->buf, iter->cur + 1);
        match = memcmp(test, ref, SHA256_LENGTH);
        count++;
    }

    if (!match) {
        puts(iter->buf);
        fprintf(stderr, "%lu total hashes\n", count);
    }
    free_alphabet_iter(iter);
    free(ref);
    free(test);
    if (match) {
        return 1;
    }
    return 0;
}
