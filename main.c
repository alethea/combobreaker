#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <sys/timeb.h>
#include "hash.h"
#include "alphabet.h"

int main() {
    char *test;
    char *ref;
    int match;
    uint64_t count;
    struct timeb start;
    struct timeb end;
    double duration;
    alphabet_iter *iter;

    match = 1;
    count = 0;
    iter = make_alphabet_iter(8);
    ref = scan_hash(SHA256_LENGTH);

    ftime(&start);
    while (match) {
        alphabet_next(iter);
        test = sha256(iter->buf, iter->cur + 1);
        match = memcmp(test, ref, SHA256_LENGTH);
        count++;
    }
    ftime(&end);
    duration = (double) (end.time - start.time);
    duration += (double) (end.millitm - start.millitm);

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
