#!/usr/bin/env python3
from random import randint, shuffle
import string
import random

letter = string.ascii_lowercase
print(''.join(random.choice(letter) for i in range(200000)))

n = 1000
print(n)
for x in range(n):
    print(''.join(random.choice(letter) for i in range(x+1)))
