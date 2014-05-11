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

    def ordering(self, total=None):
        if total is None:
            key = lambda e: e[1]
        else:
            total_max = max(total.d.values())
            key = lambda e: e[1] == 0 and total.d[e[0]] - total_max or e[1]
        return [c for c, f in sorted(self.d.items(), key=key, reverse=True)]


class Chain:
    def __init__(self, alphabet):
        self.d = OrderedDict(((c, Histogram(alphabet)) for c in alphabet))
        self.d[''] = Histogram(alphabet)
        self.t = Histogram(alphabet)

    def feed(self, password, frequency):
        last = ''
        for character in password:
            if character not in self.d:
                return
        for character in password:
            self.d[last].feed(character, frequency)
            self.t.feed(character, frequency)
            last = character

    def ordering(self):
        return OrderedDict(
                ((c, self.d[c].ordering(self.t)) for c in self.init()))

    def init(self):
        return self.d[''].ordering()


def read(filename):
    with open(filename) as f:
        reader = csv.reader(f)
        for row in reader:
            yield (row[0], int(row[1]))


def write(template, output, **kwargs):
    with open(template) as f:
        t = string.Template(f.read())
    with open(output, 'w') as f:
        f.write(t.safe_substitute(**kwargs))


def output_c(template, output, chain):
    init = chain.init()
    index = dict(zip(init, (str(x) for x in range(len(init)))))
    block = chain.ordering().items()
    a_chain = ',\n    '.join(('{{{0}}}'.format(', '.join(
        (index[x] for x in xs))) for c, xs in block))
    a_map = ', '.join(("'{0}'".format(c) for c in init))
    write(template, output, alphabet_chain=a_chain, alphabet_map=a_map)


def main():
    chain = Chain(string.ascii_lowercase + string.digits)
    for password, frequency in read(sys.argv[2]):
        chain.feed(password, frequency)
    output_c(sys.argv[1], sys.argv[-1], chain)


if __name__ == '__main__':
    main()
