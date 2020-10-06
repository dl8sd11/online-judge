n = 240
m = n * (n-1) // 2
print(n, m)

for i in range(n):
    for j in range(n):
        if i < j:
            print(i, j)

for x in range(n-1):
    print(x, end=' ')
print()
