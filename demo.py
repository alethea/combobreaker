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


def distance(a, b):
    if len(a) != len(b):
        raise ValueError('a and b must be the same length')
    dist = 0
    for i in range(len(a)):
        for j in range(8):
            if (a[i] >> j) & 1 != (b[i] >> j) & 1:
                dist += 1
    return dist
