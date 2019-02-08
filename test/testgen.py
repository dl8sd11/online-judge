#!/usr/bin/env python3
from random import randint
t = 100
print(t)

for i in range(t):
    n = randint(1,1000)
    for j in range(n):
        print(chr(97+randint(0,3)),end='')
    print()