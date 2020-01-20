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
    return randint(1,50)

n = 2000
print(n)
edg = randomTree(n)

for e in edg:
    print(e[1],e[0])
