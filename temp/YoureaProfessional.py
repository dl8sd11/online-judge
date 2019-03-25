p=input
F,I,T=map(int,p().split())
r=range
st=[p() for i in r(F)]
ans=0
for i in r(I):
    cur=0
    for j in r(F):
        if st[j][i]=='Y':
            cur+=1
    ans+=cur>=T
print(ans)
#kitten