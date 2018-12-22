#!/usr/bin/env python3
from random import randint

for i in range(30):
  n = 20000
  k = randint(1,n*(n+1)/2)
  print("{} {}".format(n,k))
  for j in range(n):
    print(randint(-10000,10000),end='')
    if j is n-1:
      print()
    else:
      print(' ',end='')
print("0 0")