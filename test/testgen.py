#!/usr/bin/env python3
from random import randint, shuffle
import string
import random

def randomString(stringLength=10):
    """Generate a random string of fixed length """
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(stringLength))
n = 2
q = 1

print(n, q)
for i in range(n):
    if i == 0:
        continue
    u = i+1
    v = randint(1, u-1)
    print("{} {} {}".format(u, v, randint(1, 20000)))

for i in range(q):
    u = randint(1, n)
    v = randint(1, n)
    while v == u:
        v = randint(1, n)
    print("{} {} {}".format(u, v, randint(1, 20000)))