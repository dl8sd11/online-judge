#!/usr/bin/env python3
from random import randint

t = randint(1,1)
print(t)
for i in range(t):
  n = randint(1,100)
  m = randint(1,10)
  print("{} {}".format(n,m))
  for j in range(m):
    if (randint(1,2) == 1):
      print("A {} {}".format(randint(1,n),randint(1,n)))
    else:
      print("D {} {}".format(randint(1,n),randint(1,n)))