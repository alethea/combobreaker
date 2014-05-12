#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>
#include "hash.h"
#include "alphabet.h"

int main() {
    char *test;
    char *ref;
    int match;
    uint64_t count;
    struct timespec start;
    struct timespec end;
    double duration;
    alphabet_iter *iter;

    match = 1;
    count = 0;
    iter = make_alphabet_iter(8);
    ref = scan_hash(SHA256_LENGTH);

    clock_gettime(CLOCK_MONOTONIC, &start);
    while (match) {
        alphabet_next(iter);
        test = sha256(iter->buf, iter->cur + 1);
        match = memcmp(test, ref, SHA256_LENGTH);
        count++;
    }
    clock_gettime(CLOCK_MONOTONIC, &end);
    duration = (double) (end.tv_sec - start.tv_sec);
    duration += ((double) (end.tv_nsec) - ((double) start.tv_nsec)) / 1000000;

    if (!match) {
        puts(iter->buf);
        fprintf(stderr, "%lu total hashes\n", count);
        fprintf(stderr, "%.2f hashes/sec\n", ((double) count) / duration);
    }
    free_alphabet_iter(iter);
    free(ref);
    free(test);
    if (match) {
        return 1;
    }
    return 0;
}
