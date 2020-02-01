#include <bits/stdc++.h>
#define max_b 47000
#define max_delta 200005
using namespace std;
int isprime1[max_b],isprime2[max_delta];
typedef unsigned long long LL;
LL kase,L,R;
void Input(LL &ret)
{
	char c;
	ret = 0;
	while((c=getchar())<'0' || c>'9');
	while(c>='0'&&c<='9') ret = ret*10 +(c-'0'),c=getchar();
}
void segment_sieve(LL a,LL b)
{
    for(LL i=0;(LL)i*i<=b;i++)
        isprime1[i]=1;
    for(LL i=0;i<=b-a;i++)
        isprime2[i]=1;
    for(LL i=2;(LL)i*i<=b;i++){
        if(isprime1[i]){
            for(LL j=i*2;j*j<=b;j+=i)
                isprime1[j]=0;
            LL k;
            if(i>=a) k=i+i;
            else if(a%i==0) k=a;
            else k=a-(a%i)+i;
            for(k;k<=b;k+=i)
                isprime2[k-a]=0;
        }
    }
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int a,b;
    Input(kase);
    while(kase--){
        Input(L);
        Input(R);
        LL ans=0;
        segment_sieve(min(L,R),max(L,R));
        for(int i=0;i<=R-L;i++){
            if(isprime2[i])
                ans++;
        }
        cout << ans << endl;
    }
    return 0;
}