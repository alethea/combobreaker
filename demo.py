#!/usr/bin/env python3

def max_len(n):
    def max_len_cond(b):
        return len(b) <= n
    return max_len_cond


def linear_sweep(cond):
    b = bytearray()
    while cond(b):
        yield bytes(b)
        c = 1
        for i in range(len(b)):
            if c == 1 and b[i] == 255:
                b[i] = 0
            else:
                b[i] += c
                c = 0
        if c == 1:
            b.append(0);
