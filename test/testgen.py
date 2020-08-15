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

n, a, b = 3, randint(1, 5), randint(1, 5)

lst = -1 
print(n, a, b)

for i in range(n):
    l = randint(lst+1, lst+5)
    r = randint(l, l+10)
    print(l, r)
    lst = r

