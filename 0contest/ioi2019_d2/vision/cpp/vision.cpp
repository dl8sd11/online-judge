#include "vision.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif


vector<int> res;
int h, w, k;

int toID (int x, int y) {
    return x * w + y;
}

void bs (int x, int y) {
    vector<int> nei;
    for (int i=0; i<h; i++) {
        for (int j=0; j<w; j++) {
            if (abs(x-i) + abs(y-j) == k) {
                nei.emplace_back(toID(i, j));
            }
        }
    }

    debug(nei, x, y);

    if (nei.size()) {
        int ore = add_or(nei);
        res.emplace_back(add_and({toID(x,y), ore}));
    }
}

void construct_network(int H, int W, int K) {
//	std::vector<int> Ns;
//	Ns = {0, 1};
//	int a = add_and(Ns);
//	Ns = {0, a};
//	int b = add_or(Ns);
//	Ns = {0, 1, b};
//	int c = add_xor(Ns);
//	add_not(c);

    h = H, w = W, k = K;
    bs(0, 0);

    add_or(res);
}
