#!/usr/bin/env python3

import sys
import csv


class Histogram:
    def __init__(self):
        self.d = {}

    def feed(self, character, frequency):
        self.d[character] = self.d.get(character, 0) + frequency

    def ordering(self):
        return [c for c, f in sorted(self.d.items(),
                                     key=lambda e: e[1],
                                     reverse=True)]


class Chain:
    def __init__(self):
        self.d = {}

    def feed(self, password, frequency):
        last = ''
        for character in password:
            try:
                self.d[last].feed(character, frequency)
            except KeyError:
                self.d[last] = Histogram()
                self.d[last].feed(character, frequency)
            last = character

    def ordering(self):
        res = {}
        for character, following in self.d.items():
            res[character] = following.ordering()
        return res


def read(filename):
    with open(filename) as f:
        reader = csv.reader(f)
        for row in reader:
            yield (row[0], int(row[1]))


def main():
    chain = Chain()
    for password, frequency in read(sys.argv[1]):
        chain.feed(password, frequency)
    for c, f in chain.ordering().items():
        print(c, f)


if __name__ == '__main__':
    main()
