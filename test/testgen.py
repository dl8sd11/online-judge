#!/usr/bin/env python3
from random import randint
n = 100000
c = 1000000000
print("{} {}".format(n,n))
for i in range(n):
    print(randint(1,c),end=" ")
print()


for i in range(n):
    l , r = randint(1,n) , randint(1,n)
    if l > r:
        l,r = r,l
    if randint(1,2) == 1:
        print("{} {} {}".format(1,l,r))
    else:
        print("{} {} {}".format(2,randint(1,n),randint(1,c)))