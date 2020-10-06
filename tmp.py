n = int(input())
x = [1, 3]
s = [[1, 1], [1, 0]]
plus = [[1, 0],[0, 1]]
pluss = [[1, 0],[0, 1]]
ss = [[0, 0], [0, 0]]
ans = [[0, 0], [0, 0]]

import copy
while n // 2 > 0:

    if n % 2 == 0:
        n //= 2
        
        for i in range(2):
            for j in range(2):
                ss[i][j] = s[i][0] * s[0][j] + s[i][1] * s[1][j]
        s = copy.deepcopy(ss)

    else:
        n //= 2
        for i in range(2):
            for j in range(2):
                pluss[i][j] = s[i][0] * plus[0][j] + s[i][1] * plus[1][j]
        plus = copy.deepcopy(pluss)
        for i in range(2):
            for j in range(2):
                ss[i][j] = s[i][0] * s[0][j] + s[i][1] * s[1][j]
        s = ss.copy()

for i in range(2):
    for j in range(2):
        ans[i][j] = s[i][0] * plus[0][j] + s[i][1] * plus[1][j]

print(ans)
