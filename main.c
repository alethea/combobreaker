#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hash.h"
#include "alphabet.h"

int main() {
    char *test;
    char *ref;
    int match;
    alphabet_iter *iter;

    match = 1;
    iter = make_alphabet_iter(8);
    ref = scan_hash(SHA256_LENGTH);

    while (match) {
        alphabet_next(iter);
        test = sha256(iter->buf, iter->cur + 1);
        match = memcmp(test, ref, SHA256_LENGTH);
    }

    if (!match) {
        puts(iter->buf);
    }
    free_alphabet_iter(iter);
    free(ref);
    free(test);
    if (match) {
        return 1;
    }
    return 0;
}
