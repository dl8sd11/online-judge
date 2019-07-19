#!/usr/bin/env python3
from random import randint, shuffle

t = 100
print(t)

for i in range(t):
    n = randint(100,100)
    z = randint(1,n)
    print("{} {}".format(n, z))
    for x in range(n):
        print(randint(1,10), end=' ')
    print()