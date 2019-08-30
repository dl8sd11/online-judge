#!/usr/bin/env python3
from random import randint, shuffle
import string
import random

def randomString(stringLength=10):
    """Generate a random string of fixed length """
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(stringLength))


n = 1
w = 3
print("{} {}".format(n, w))

for i in range(n):
    l = randint(1, w)
    a = []
    a.append(l)
    for j in range(l):
        a.append(randint(-10, 10))
    for x in a:
        print(x, end=' ')
    print()