#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define eb emplace_back
#define X first
#define Y second
#define ALL(i) i.begin(),i.end()
#define MEM(i,a) memset(i,(a),sizeof(i))
#ifdef tmd
#define debug(...) fprintf(stderr,"%d(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x) {
    cerr<<x<<endl;
}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {
    cerr<<x<<",";
    _do(y...);
}
template<typename IT> ostream& _print(IT bg, IT ed, ostream &os) {
    for (IT it=bg;it!=ed; it++) {
        if (it==bg) {
            os << "{" << *it;
        } else {
            os << "," << *it;
        }
    }
    return os << "}";
}
template<typename IT> void pary (IT bg, IT ed) {
    _print(bg, ed, cerr);
}
template<typename T> ostream& operator<< (ostream &os, const vector<T> &vec) {
    return _print(vec.begin(), vec.end(),os);
}
#define IOS()
#else
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define debug(...)
#define pary(...)
#endif // tmd

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

/*******GOODLUCK*********/
int main () {
    IOS();

    return 0;
}
