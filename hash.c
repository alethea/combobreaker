#include <stdio.h>
#include <stdlib.h>
#include "hash.h"
#include <string.h>

char * sha256(char * message, size_t length){
	char * digest= (char *) malloc(SHA256_LENGTH);
	memset(digest, 0, SHA256_LENGTH);
	return digest;
}