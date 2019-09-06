#!/usr/bin/env python3
from random import randint, shuffle
import string
import random

def randomString(stringLength=10):
    """Generate a random string of fixed length """
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(stringLength))


n = 1000
k = 0
print(n)
print(k)

p1 = []
q1 = []


for i in range(n):
    p1.append(i+1)
    q1.append(i+1)

shuffle(p1)
shuffle(q1)