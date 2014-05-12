__constant uint H0[8] = {
    0x6a09e667,
    0xbb67ae85,
    0x3c6ef372,
    0xa54ff53a,
    0x510e527f,
    0x9b05688c,
    0x1f83d9ab,
    0x5be0cd19
}; 

__constant uint K[64]= {
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

#define Ch(x, y, z) ((x & y) ^ (~x & z))

#define Maj(x, y, z) ((x & y) ^ (x & z) ^ (y & z))

#define S0(x) (rotate(x, -2U) ^ rotate(x, -13U) ^ rotate(x, -22U))

#define S1(x) (rotate(x, -6U) ^ rotate(x, -11U) ^ rotate(x, -25U))

#define d0(x) (rotate(x, -7U) ^ rotate(x, -18U) ^ (x >> 3))

#define d1(x) (rotate(x, -17U) ^ rotate(x, -19U) ^ (x >> 10))

#define endian_swap(x) (rotate(x & 0x00ff00ff, 24U) | (rotate(x, 8U) & 0x00ff00ff))

__kernel void sha256(__global char *message, __global int *length, __global uint *hash) {
    uint T1, T2;
    uint W[64];
    uint M[16];
    uchar *Mchar = (uchar *) M;
    uint reg[8];
    int j, k;
    
    for (k = 0; k < 15; k++) {
        M[k] = 0;
    }
    for (k = 0; k < *length; k++) {
        Mchar[k] = message[k];
    }
    Mchar[*length] = 0x80;
    #ifdef __LITTLE_ENDIAN__
        M[15] = endian_swap((uint) *length * 8);
    #else
        M[15] = *length * 8;
    #endif

    for (k = 0; k < 8; k++) {
        reg[k] = H0[k];
    }
    for (j = 0; j <= 63; j++) {
        if (j < 16) {
            #ifdef __LITTLE_ENDIAN__
                W[j] = endian_swap(M[j]);
            #else
                W[j] = M[j];
            #endif
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
        #ifdef __LITTLE_ENDIAN__
        hash[k] = endian_swap(reg[k] + H0[k]);
        #else
        hash[k] = reg[k] + H0[k];
        #endif
    }
}
