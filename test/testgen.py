#!/usr/bin/env python3
from random import randint
t = 5
print(t)
for tc in range(t):
    n = 100000
    k = randint(1,1000000)
    print("{} {}".format(n,k))


    for i in range(n):
        print(randint(1,100000),end=' ')
    print()