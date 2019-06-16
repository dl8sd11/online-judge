l = int(input())
n = input()



first = l//2 + 1
second = l//2
while second < l and n[second] == '0':
    second += 1

while n[first] == '0':
    first -= 1

ans = -1
if second == l:
    ans = int(n[0:first]) + int(n[first:l])
elif first == 0:
    ans = int(n[0:second]) + int(n[second:l])
else:
    ans = min(int(n[0:second]) + int(n[second:l]),int(n[0:first]) + int(n[first:l]))

print(ans)
