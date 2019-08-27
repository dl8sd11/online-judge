#!/usr/bin/env python3
from random import randint, shuffle
import string
import random

def randomString(stringLength=10):
    """Generate a random string of fixed length """
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(stringLength))


n = 100000
m = 100000

print("{} {}".format(n, m))
for i in range(n-1):
    print("{}".format(randint(1, i+1)))

for i in range(m):
    u = randint(1, n)
    v = u + randint(1, n-1)
    if v > n:
        v -= n
    if u > v:
        u, v= v, u
    print("{} {}".format(u, v))
