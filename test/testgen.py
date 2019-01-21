#!/usr/bin/env python3
from random import randint
n = randint(1,100000)
m = randint(1,n)
print("{} {}".format(n,m))

for i in range(n):
    if (randint(1,2) == 1):
        print("H",end='')
    else:
        print("G",end='')
print()