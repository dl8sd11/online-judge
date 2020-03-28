t = int(input())

ans = 0
fnd = False

def dfs (nd, p1, p2):
    sum = p1[0] + p1[1]
    if p1[0] > p2[0] or p1[1] > p2[1]:
        return

    global fnd
    global ans
    if p1 == p2:
        while(fnd):
            pass
        fnd = True
        ans = nd
    else:
        dfs(nd*2, (p1[0], sum), p2)
        dfs(nd*2+1, (sum, p1[1]), p2)


def solve(p1, p2):
    global fnd
    global ans
    fnd = False
    dfs(1, p1, p2)
    return ans if fnd else -1

for ts in range(t):
    a,b,c,d = [int(x) for x in input().split(' ')]

    print(solve((a,b),(c,d)))

