#!/usr/bin/env python3
from random import randint, shuffle
import string
import random

def randomString(stringLength=10):
    """Generate a random string of fixed length """
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(stringLength))

def randomTree(sz):
    edg = []
    for i in range(1, sz):
        edg.append((i, randint(0, i-1)))
    return edg

def get_perm(sz):
    a = [x for x in range(1,sz+1)]
    shuffle(a)
    return a

def genInt ():
    return randint(1,10)

n = 100000
q = 100000
W = 100000

print(n, q)
edg = randomTree(n)

for x in range(n):
    print(0, end=' ')
print()

for e in edg:
    print(e[0]+1, e[1]+1, randint(1, W))


for qq in range(q):
    if qq > 1000:
        print(1, randint(1, n))
    else:
        print(2, randint(1, 1000000000), randint(1, W), 1)