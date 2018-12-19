#!/usr/bin/env python3
from random import randint

n = randint(1,10)
m = randint(1,10)
print("{} {}".format(n,m))
for i in range(n):
  print("{} {} {}".format(randint(0,10),randint(0,10),randint(0,10)))

for i in range(m):
  print("{} {}".format(randint(0,10),randint(0,10)))