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

def getChar ():
    x = "AKQJ"
    if randint(1,13) <= 4:
        return random.choice(x)
    else :
        return str(randint(2, 10))

n = randint(3, 4)
a = [str(randint(1, 10)) for x in range(n)]
print(n)
print(" ".join(a))
