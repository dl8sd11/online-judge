
def solve (x):
    res = -1
    par = [0, 0, 0, 0]

    for mn in range(1, 1000):
        pre11 = 0
        for i in range(mn):
            pre11 = pre11 * 10 + 1
            pre11 %= x

        suf11 = 0
        pw = 1
        for n in range(1, mn):
            suf11 = suf11 * 10 + 1
            suf11 %= x

            pre11 = pre11 - pw + x
            pre11 %= x

            pw *= 10
            pw %= x

            m = mn - n

            prexx = 0
            for s in range(1, 10):
                prexx += pre11
                prexx %= x
                sufxx = 0
                for t in range(0, 10):
                    num = prexx + sufxx
                    num %= x
                    if s != t:
                        if num == 0 and (res == -1 or [par[1],par[0],par[3]] > [s,m,t]):
                            res = num
                            par = [m, s, n, t]
                    sufxx += suf11
                    sufxx %= x
        if res != -1:
            break
    return par

from random import randint
while True:
    x = int(input())
    if x == 0:
        break
    m, s, n, t = solve(x)
    print("{}: {} {} {} {}".format(x, m ,s, n, t))
