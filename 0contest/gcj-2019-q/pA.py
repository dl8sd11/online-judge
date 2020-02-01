T = int(input())
for i in range(T):
    n = int(input())
    a = 0
    b = 0
    rate = 1
    idx = 1
    while n > 0:
        ld = n % 10
        n = n // 10
        da = ld // 2
        db = ld - da
        if idx % 2 == 0:
            da,db = db,da

        if da == 4 or db == 4:
            da -= 1 if da < db else -1
            db += 1 if da < db else -1

        a += da * rate
        b += db * rate
        rate *= 10
        idx += 1
    if a == 0:
        a += 1
        b -= 1

    if b == 0:
        a -= 1
        b += 1
    print("Case #{}: {} {}".format(i+1,a,b))