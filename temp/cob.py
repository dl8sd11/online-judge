res = []
def cob (n, available, cur):
    if n == 0:
        res.append(cur.copy())
    else:
        for x in available:
            if n - x >= 0 and (not cur or x <= cur[-1]):
                cur.append(x)
                cob(n - x, available, cur)
                cur.pop()

cob(4, [3, 2, 1], [])
print(res)

