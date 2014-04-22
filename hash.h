#ifndef _COMBOBREAKER_HASH_H_
#define _COMBOBREAKER_HASH_H_

#include <stdlib.h>

#define SHA256_LENGTH 32

char *sha256(const char *message, size_t length);

#endif
