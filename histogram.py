#!/usr/bin/env python3

import sys
import csv
import string
from collections import OrderedDict


class Histogram:
    def __init__(self, alphabet):
        self.d = OrderedDict(((c, 0) for c in alphabet))

    def feed(self, character, frequency):
        self.d[character] += frequency

    def ordering(self):
        return [c for c, f in sorted(self.d.items(),
                                     key=lambda e: e[1],
                                     reverse=True)]


class Chain:
    def __init__(self, alphabet):
        self.d = OrderedDict(((c, Histogram(alphabet)) for c in alphabet))
        self.d[''] = Histogram(alphabet)

    def feed(self, password, frequency):
        last = ''
        for character in password:
            if character not in self.d:
                return
        for character in password:
            self.d[last].feed(character, frequency)
            last = character

    def ordering(self):
        return OrderedDict(((c, f.ordering()) for c,f in self.d.items()))


def read(filename):
    with open(filename) as f:
        reader = csv.reader(f)
        for row in reader:
            yield (row[0], int(row[1]))


def main():
    chain = Chain(string.ascii_lowercase + string.digits)
    for password, frequency in read(sys.argv[1]):
        chain.feed(password, frequency)
    for c, f in chain.ordering().items():
        print(c, ' '.join(f))


if __name__ == '__main__':
    main()
