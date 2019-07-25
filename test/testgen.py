#!/usr/bin/env python3
from random import randint, shuffle

t = 100
print(t)

for i in range(t):
    n = randint(1,1000)
    z = 1000
    print("{} {}".format(n, z))
    for x in range(z):
        if randint(1,2) == 1:
            print("1 {}".format(randint(1,n)))
        else:
            l = randint(1,n)
            r = randint(1,n)
            if l > r:
                l, r = r, l
            print("2 {} {}".format(l, r))
    print()