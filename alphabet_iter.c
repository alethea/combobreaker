#include <stdlib.h>
#include <stdint.h>
#include "alphabet.h"

alphabet_iter *make_alphabet_iter(int max_length) {
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

char *alphabet_next(alphabet_iter *iter) {
    int i;

    iter->buf[0] = alphabet_map[iter->idx[0]];
    for (i = 1; i <= iter->cur; i++) {
        iter->buf[i] = alphabet_map[alphabet_chain[iter->off[i]][iter->idx[i]]];
    }
    i = iter->cur;
    while (i >= 0) {
        iter->idx[i]++;
        iter->off[0] = iter->idx[0];
        if (iter->idx[i] >= ALPHABET_SIZE) {
            iter->idx[i] = 0;
            i--;
            if (i < 0) {
                iter->cur++;
            }
        } else {
            break;
        }
    }
    for (i = 1; i <= iter->cur; i++) {
        iter->off[i] = alphabet_chain[iter->off[i - 1]][iter->idx[i - 1]];
    }
    return iter->buf;
}
