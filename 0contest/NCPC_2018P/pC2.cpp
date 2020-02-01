#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll,ll> pll;
typedef long double ld;
const ll N=2e3+5;
const ll MOD=1e9+7;
const ll INF=(1LL<<60);
const ld pi=3.14159265359;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define pb push_back
#define mp make_pair
#define X first
#define Y second
#define lwb lower_bound
#define setp setprecision
#define SZ(a) (ll)a.size()

ll t,n,ans[3];

ll lcm(ll a[]){
    ll g=a[0]*a[1]/__gcd(a[0],a[1]);
    return g*a[2]/__gcd(g,a[2]);
}

void ck(ll k){
    if(n/k<3)return;
    ll u[3];
    u[0]=k;ll g=n/k-1;
    for(ll i=1;i*i<=g;i++){
        if(g%i!=0)continue;
        if(g/i>=2){u[1]=k*i;u[2]=k*i*(g/i-1);
        if(lcm(u)<=lcm(ans))REP(j,3)ans[j]=u[j];
        if(i>=2){u[1]=k*g/i;u[2]=k*g/i*(i-1);}
        if(lcm(u)<=lcm(ans))REP(j,3)ans[j]=u[j];
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    while(cin>>n){
        ans[0]=ans[1]=1;ans[2]=n-2;
        for(ll i=1;i*i<=n;i++){
            if(n%i==0){
                ck(i);
                ck(n/i);
            }
        }
        REP(i,3)cout<<ans[i]<<(i==2?"\n":" ");
    }
    return 0;
}
