#!/usr/bin/env python3

import sys
from hashlib import sha256

def main():
    h = sha256()
    h.update(sys.argv[1].encode('ascii'))
    print(h.hexdigest())

if __name__ == '__main__':
    main()
