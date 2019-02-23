ss = "1 2 3 ".join(["dog","cat"])
print(ss)
n = int(input())
for i in range(n):
    li = input().split(" ")
    li = [int(i) for i in li]
    if li[1] - li[0] == li[2] - li[1]:
        li.append(li[3] + li[1] - li[0])
    else:
        li.append(li[3] * (li[1] // li[0]))
    li = [str(i) for i in li]
    print(" ".join(li))

