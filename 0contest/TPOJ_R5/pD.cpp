#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<(k) ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=(k) ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef tmd
#define TIME(i) Timer i(#i)
#define debug(...) do{\
    fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);\
    _do(__VA_ARGS__);\
}while(0)
template<typename T>void _do(T &&_x){cerr<<_x<<endl;}
template<typename T,typename ...S> void _do(T &&_x,S &&..._t){cerr<<_x<<" ,";_do(_t...);}
template<typename _a,typename _b> ostream& operator << (ostream &_s,const pair<_a,_b> &_p){return _s<<"("<<_p.X<<","<<_p.Y<<")";}
template<typename It> ostream& _OUTC(ostream &_s,It _ita,It _itb)
{
    _s<<"{";
    for(It _it=_ita;_it!=_itb;_it++)
    {
        _s<<(_it==_ita?"":",")<<*_it;
    }
    _s<<"}";
    return _s;
}
template<typename _a> ostream &operator << (ostream &_s,vector<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,set<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a> ostream &operator << (ostream &_s,deque<_a> &_c){return _OUTC(_s,ALL(_c));}
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 300005;

int n, hei[MAXN];
vector<int> edge[MAXN];

int findFarBuildHei (int nd, int par) {
    hei[nd] = 1;
    int mxHei = 0, ret = nd;
    for (auto v : edge[nd]) {
        if (v != par) {
            int cur = findFarBuildHei(v, nd);
            if (hei[v] > mxHei) {
                mxHei = hei[v];
                ret = cur;
            }
            hei[nd] = max(hei[nd], hei[v] + 1);
        }
    }
    return ret;
}

void buildChain (int nd, int par, vector<int> &chain) {
    chain.emplace_back(nd);

    int mxHei = 0, ret = -1;
    for (auto v : edge[nd]) {
        if (v != par) {
            if (hei[v] > mxHei) {
                mxHei = hei[v];
                ret = v;
            }
        }
    }

    if (ret > 0) {
        buildChain(ret, nd, chain);
    }
}

int ans[MAXN];
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n;
    REP (i, n-1) {
        int u, v;
        cin >> u >> v;
        edge[u].emplace_back(v);
        edge[v].emplace_back(u);
    }

    int root = findFarBuildHei(1, 1);
    int __not_used__ = findFarBuildHei(root, root);
    debug(root, __not_used__);

    vector<int> chain;
    chain.reserve(hei[root]);

    buildChain(root, root, chain);
    debug(chain);

    { // fill chain
        int oddSZ = SZ(chain) / 2;
        int evenSZ = SZ(chain) - oddSZ;
        vector<int> odd(oddSZ), even(evenSZ);

        odd[0] = oddSZ;
        REP (i, oddSZ - 1) {
            odd[i+1] = 1 + i;
        }
        reverse(odd.begin(), odd.end());

        even[0] = n + 1 - evenSZ;
        REP (i, evenSZ - 1) {
            even[i+1] = n - i;
        }

        REP (i, oddSZ) {
            ans[chain[i*2+1]] = odd[i];
        }
        REP (i, evenSZ) {
            ans[chain[i*2]] = even[i];
        }

        int idx = 1;
        for (int i=oddSZ+1; i<=n-evenSZ; i++) {
            while (ans[idx] != 0) {
                idx++;
            }
            ans[idx] = i;
        }
    }

    REP1 (i, n) {
        cout << ans[i] << " \n"[i==n];
    }
    return 0;
}
