#include <stdlib.h>
#include <stdint.h>
#include "alphabet.h"

alphabet_iter *make_alphabet_iter(size_t max_length) {
    alphabet_iter *iter;

    iter = calloc(1, sizeof (alphabet_iter));
    iter->buf = calloc(max_length + 1, sizeof (char));
    iter->idx = calloc(max_length, sizeof (int8_t));
    iter->off = calloc(max_length, sizeof (int8_t));
    iter->len = max_length;
    return iter;
}

void free_alphabet_iter(alphabet_iter *iter) {
    free(iter->buf);
    free(iter->idx);
    free(iter->off);
    free(iter);
}
