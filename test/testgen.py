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

n, k, q = 3, 5, 3 

print(n, k, q)
res = [x+1 for x in range(100)]
shuffle(res)

ptr = 0
def get_next ():
    global ptr
    ptr +=1
    return res[ptr]

for i in range(n):
    print(get_next(), end=' ')

print()

r = []
for i in range(k):
    r.append(randint(1, n))
    print(r[-1], end=' ')
    for x in range(r[-1]):
        print(get_next(), end=' ')
    print()

for i in range(q):
    rid = randint(0, k-1)
    print(rid+1, randint(1, r[rid]), get_next())

