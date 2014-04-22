#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <endian.h>
#include "hash.h"

const uint32_t H0[8] = {
	0x6a09e667,
	0xbb67ae85,
	0x3c6ef372,
	0xa54ff53a,
	0x510e527f,
	0x9b05688c,
	0x1f83d9ab,
	0x5be0cd19
}; 

const uint32_t K[64]= {
	0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
	0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
	0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 
	0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85, 
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
	0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
	0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2

};

typedef enum {
    a, b, c, d, e, f, g, h
} sha256_reg_t;

uint32_t rotr(uint32_t i, uint32_t x) {
    return (x >> i) | (x << (sizeof(x) * 8 - i));
}

uint32_t Ch(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (~x & z);
}

uint32_t Maj(uint32_t x, uint32_t y, uint32_t z) {
    return (x & y) ^ (x & z) ^ (y & z);
}

uint32_t S0(uint32_t x) {
    return rotr(2, x) ^ rotr(13, x) ^ rotr(22, x);
}

uint32_t S1(uint32_t x) {
    return rotr(6, x) ^ rotr(11, x) ^ rotr(25, x);
}

uint32_t d0(uint32_t x) {
    return rotr(7, x) ^ rotr(18, x) ^ (x >> 3);
}

uint32_t d1(uint32_t x) {
    return rotr(17, x) ^ rotr(19, x) ^ (x >> 10);
}

uint32_t *prepare(const char *message, size_t length, size_t N) {
    size_t Nchar = N * 64;
    char *M = (char *) malloc(Nchar);
    uint64_t *l = (uint64_t *) M + N * 8 - 1;

    memcpy(M, message, length);
    M[length] = '\x80';
    memset(M + length + 1, 0, Nchar - length - 9); 
    *l = htobe64(length * 8);
    return (uint32_t *) M;
}

char *sha256(const char *message, size_t length) {
    size_t N = (length + 72) / 64;
    size_t i, j, k;
    uint32_t T1, T2;
    uint32_t W[64];
    uint32_t *M = prepare(message, length, N);
    uint32_t *H = (uint32_t *) malloc(32);
    uint32_t reg[8];

    memcpy(H, H0, 32);

    for (i = 0; i < N; i++) {
        memcpy(reg, H, 32);
        for (j = 0; j <= 63; j++) {
            if (j < 16) {
                W[j] = be32toh(M[i * 16 + j]);
            } else {
                W[j] = d1(W[j - 2]) + W[j - 7] + d0(W[j - 15]) + W[j - 16];
            }
            T1 = reg[h] + S1(reg[e]) + Ch(reg[e], reg[f], reg[g]) + K[j] + W[j];
            T2 = S0(reg[a]) + Maj(reg[a], reg[b], reg[c]);
            reg[h] = reg[g];
            reg[g] = reg[f];
            reg[f] = reg[e];
            reg[e] = reg[d] + T1;
            reg[d] = reg[c];
            reg[c] = reg[b];
            reg[b] = reg[a];
            reg[a] = T1 + T2;
        }
        for (k = 0; k < 8; k++) {
            H[k] = reg[k] + H[k];
        }
    }

    for (k = 0; k < 8; k++) {
        H[k] = htobe32(H[k]);
    }

    free(M);
    return (char *) H;
}
