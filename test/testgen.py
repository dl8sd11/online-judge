#!/usr/bin/env python3
from random import randint, shuffle
import string
import random

def randomString(stringLength=10):
    """Generate a random string of fixed length """
    letters = string.ascii_lowercase
    return ''.join(random.choice(letters) for i in range(stringLength))


q = 10
k = randint(2, 10)

print("{} {}".format(q, k))
for i in range(q):
    print(i+1)