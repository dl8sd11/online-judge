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
    for i in range(2, sz+1):
        edg.append((i, randint(1, i-1)))
    return edg

n = 3
q = 10

def genInt ():
    return randint(-50,50)

print(n, q)
for i in range(n):
    print(genInt(), end=' ')
print()
for i in range(n):
    print(randint(1,n), end=' ')
print()

for i in range(q):
    print(genInt(), genInt())