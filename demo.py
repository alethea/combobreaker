#!/usr/bin/env python3

import hashlib


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


def digest(algo, string):
    h = hashlib.new(algo)
    h.update(string)
    return h.digest()


def max_distance(algo):
    return hashlib.new(algo).digest_size * 8


def shortest(algo, space, ref):
    min_dist = max_distance(algo)
    min_string = None
    for string in space:
        dist = distance(digest(algo, string), ref)
        if dist < min_dist:
            min_dist = dist
            min_string = string
    return (min_dist, min_string)


def demo(algo, n, ref_string):
    print('Reference string:', ref_string)
    print('Algorithm:', algo)
    print('Maximum distance:', max_distance(algo))
    d, s = shortest(algo, linear_sweep(max_len(n)), digest(algo, ref_string))
    print('Minium distance:', d)
    print('Closest string:', repr(s))


if __name__ == '__main__':
    demo('md5', 2, b'hi')
    demo('md5', 2, b'hello')
