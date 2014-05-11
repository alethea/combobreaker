#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "alphabet.h"

int main() {
    int i;
    alphabet_iter *iter;

    iter = make_alphabet_iter(8);
    for (i = 0; i < 8192; i++) {
        puts(alphabet_next(iter));
    }
    free_alphabet_iter(iter);
    return 0;
}
