#!/usr/bin/env python3
from random import randint, shuffle

t = 1
print(t)

for i in range(t):
    n = randint(1,10000)
    q = randint(1, 5)
    print("{} {}".format(n, q))
    for x in range(n):
        print(randint(2,1000000),end=" ")
    print()
    for qq in range(q):
        l = randint(1, n)
        r = randint(1, n)
        v = randint(2,1000000)
        if l > r:
            l, r = r, l
        
        if randint(1,2) == 1:
            print("0 {} {} {}".format(l,r,v))
        else:
            print("1 {} {}".format(l, r))