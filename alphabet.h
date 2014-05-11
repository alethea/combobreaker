#ifndef _COMBOBREAKER_ALPHABET_H_
#define _COMBOBREAKER_ALPHABET_H_
#include <stdint.h>

#define ALPHABET_SIZE 36

extern const int8_t alphabet_chain[ALPHABET_SIZE][ALPHABET_SIZE];
extern const char alphabet_map[ALPHABET_SIZE];

typedef struct {
    char *buf;
    int8_t *idx;
    int8_t *off;
    int len;
    int cur;
} alphabet_iter;

alphabet_iter *make_alphabet_iter(int max_length);
void free_alphabet_iter(alphabet_iter *iter);
char *alphabet_next(alphabet_iter *iter);

#endif
