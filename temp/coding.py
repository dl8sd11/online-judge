from decimal import *
import math

dpf = []
dpn = []

trf = [0]
trn = [0]


dpn.append(Decimal(1))
dpf.append(Decimal(0))

n = int(input())

a = [int(x) for x in input().split(' ')]

nt = [Decimal(0.5), Decimal(0.4), Decimal(0.1)]
ft = [Decimal(0.1), Decimal(0.3), Decimal(0.6)]


print(n, a)
for i in range(1,n):

    n2n = dpn[i-1]*Decimal(0.7)
    f2n = dpf[i-1]*Decimal(0.4)

    n2f = dpn[i-1]*Decimal(0.3)
    f2f = dpf[i-1]*Decimal(0.6)

    if (n2n > f2n):
        dpn.append(n2n * nt[a[i]-1])
        trn.append(0)
    else:
        dpn.append(f2n * nt[a[i]-1])
        trn.append(1)

    if n2f > f2f:
        dpf.append(n2f * ft[a[i]-1])
        trf.append(0)
    else:
        dpf.append(f2f * ft[a[i]-1])
        trf.append(1)

idx = n-1

fever = 1 if dpf[n-1] > dpn[n-1] else 0

ans = []
while idx >= 0:

    ans.append("f" if fever == 1 else "h")

    fever = trf[idx] if fever == 1 else trn[idx]
    idx-=1

ans = ans[::-1]
print(ans.count('h'))
