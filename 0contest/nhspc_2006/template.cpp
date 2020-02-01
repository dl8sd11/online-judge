#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#define eb emplace_back
#define MEM(a,b) memset(a,(b),sizeof(a))
#define ALL(i) i.begin(),i.end()
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d (%s)=",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<",";_do(y...);}
template<typename IT> ostream&  __printRng(ostream &os, IT bg, IT ed) {
    os << "{";
    for (IT it=bg;it!=ed;it++) {
        cout << (it==bg?"":",") << *it;
    }
    os << "}";
    return os;
}
template<typename T> ostream& operator << (ostream &os, vector<T> &vec) {
    return __printRng(os, vec.begin(), vec.end());
}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif // tmd

const ll INF = 0x3f3f3f3f3f3f3f3f;

/*********Good***Luck*********/
int main () {
    IOS();

    return 0;
}
