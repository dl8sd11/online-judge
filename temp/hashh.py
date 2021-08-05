t = "3141592653589793"
p = "41592"

for x in range(len(t) - len(p) + 1):
    tt = t[x:x+len(p)]
    if int(tt) % 17 == int(p) % 17 and tt != p:
        print(f"Hit: {tt}")
