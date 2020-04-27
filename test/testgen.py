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
        edg.append((i+1, randint(0, i-1)+1))
    return edg

def get_perm(sz):
    a = [x for x in range(1,sz+1)]
    shuffle(a)
    return a

def genInt ():
    return randint(1,10)

n = 1000000
q = 1000000
print(n,q)
edg = randomTree(n)


for e in edg:
    print(e[0], e[1], randint(1,2))

a = 0
b = 0

for i in range(n-1):
    u = randint(1,10)
    v = randint(1,10)
    print(u,v)
    a += u
    b += v;
print(b, a)

for i in range(q):
    [u,v] = random.sample(range(1,n+1), 2)
    print(u,v)
