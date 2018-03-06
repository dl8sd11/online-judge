#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define SZ(i) ll(i.size())
#ifdef tmd
#define debug(...) do{fprintf(stderr,"%s - %d = (%s)",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);}while(0)
template<typename T>void _do(T &&x){cerr<<x<<endl;}
#else
#define debug(...)
#endif

const ll MOD = (ll)1e9 + 103;
const ll MAXN = (ll)1e4 + 3;
ll pre[MAXN];
ll t,n,mt=1;
string s,p;
int main(){
    cin>>t;
    while(t--) {
      cin>>s>>n;
      mt=1;
      pre[0]=s[0];
      REP1(i,SZ(s)-1) mt=mt*880301,pre[i]=pre[i-1]+s[i]*mt;
      while(n--) {
        cin>>p;
        if(SZ(p)>SZ(s)){cout<<0<<endl;continue;}
        ll hashi = 0;
        mt=1;
        REP(i,SZ(p))hashi=hashi+p[i]*mt,mt=mt*880301;
        ll ret=0;
        debug(hashi);
        debug(pre[1]);
        if(pre[SZ(p)-1]==hashi)ret++;
        hashi=880301*hashi;
        for(ll i=1;i<=SZ(s)-SZ(p);i++,hashi=880301*hashi)if(pre[SZ(p)+i-1]-pre[i-1]==hashi)ret++;
        cout<<ret<<endl;
      }
    }
}
