/*input

*/
#include<stdio.h>
#include<iostream>
#include<ctime>
using namespace std;

typedef long long ll;
ll mymul(ll a,ll b,ll n){
    ll ret=0;
    a %= n;
    b %= n;
    while(b){
        if(b&1){
            ret+=a;
            if(ret>=n) ret-=n;
        }
        a<<=1;
        if(a>=n) a-=n;
        b>>=1;
    }
    return ret;
}
ll mul(ll a,ll b,ll n){
    return (__int128)a*b%n;
}

ll C=48572759385058LL,D=2749503759683634LL;
ll cur=2940703473930072LL;
ll get(){
    cur=(cur+C)^D;
    return cur<0?-cur:cur;
}

int main()
{
    time_t st=clock();
    int T=100000;
    ll cnt = 0;
    while(T--){
      ll a = get(),b = get(), c=get();
        if(mymul(a,b,c) != mul(a,b,c))cnt++;
    }
    printf("%d",cnt);
    printf("%.6f\n",(double)(clock()-st)/CLOCKS_PER_SEC);
    return 0;
}
