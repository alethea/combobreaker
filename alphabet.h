#ifndef _COMBOBREAKER_ALPHABET_H_
#define _COMBOBREAKER_ALPHABET_H_
#include <stdlib.h>
#include <stdint.h>

#define ALPHABET_SIZE 36

extern const int8_t alphabet_chain[ALPHABET_SIZE][ALPHABET_SIZE];
extern const char alphabet_map[ALPHABET_SIZE];

typedef struct {
    char *buf;
    int8_t *idx;
    int8_t *off;
    size_t len;
} alphabet_iter;

alphabet_iter *make_alphabet_iter(size_t max_length);
void free_alphabet_iter(alphabet_iter *iter);

#endif
