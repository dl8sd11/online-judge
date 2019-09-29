#!/usr/bin/env python3
from random import randint, shuffle
import string
import random

def randomString(stringLength=10):
    """Generate a random string of fixed length """
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(stringLength))


n = 1000000
print(n)
for i in range(n):
    print(randint(1, 1000001), end=" ")
print()

for i in range(2, n+1):
    print(randint(1, i), end=" ")
print()