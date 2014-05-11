#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "alphabet.h"

int main() {
    alphabet_iter *iter;

    iter = make_alphabet_iter(8);
    free_alphabet_iter(iter);
    return 0;
}
