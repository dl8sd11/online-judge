#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef pair<int, ll> pil;
typedef pair<int, ll> pli;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
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
#else
#define TIME(i)
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif
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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 1003;

int n, m[MAXN], e[MAXN][11], q, pre[MAXN], dp[MAXN*100], sz[MAXN];
int edg[MAXN*100];
ll k[MAXN];
bool vis[MAXN*100];

int getID(int nd, int md) {
    return pre[nd-1] + md;
}

ll reg (ll x, ll m) {
    x %= m;
    if (x < 0) {
        x += m;
    }
    return x;
}


void findCycle (int nd) {
    int cur = nd, sz = 1;
    while (edg[cur] != nd) {
        cur = edg[cur];
        sz++;
    }
    dp[nd] = sz;
}

void solve (int nd) {
    if (dp[nd] != -1) {
        return;
    }
    vis[nd] = true;
    if (dp[edg[nd]] == -1) {
        if (vis[edg[nd]]) {
            findCycle(edg[nd]);
        } else {
            solve(edg[nd]);
        }
    }
    dp[nd] = dp[edg[nd]];
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n;
    REP1 (i, n) {
        cin >> k[i];
    }

    REP1 (i, n) {
        cin >> m[i];
        pre[i] = pre[i-1] + m[i];
        REP (j, m[i]) {
            cin >> e[i][j];
        }
    }


    REP1 (i, n) {
        REP (j, m[i]) {
            int to = e[i][reg(j+k[i], m[i])];
            edg[getID(i, j)] = getID(to, reg(j+k[i], m[to]));
            debug(i, j, to, reg(j+k[i], m[to]), reg(j+k[i], m[i]));
            debug(getID(i, j),getID(to, reg(j+k[i], m[to])));
        }
    }


    MEM(dp, -1);
    REP1 (i, n) {
        REP (j, m[i]) {
            solve(getID(i, j));   
            debug(dp[getID(i, j)], getID(i, j));     
        }
    }

    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        debug(getID(x, reg(y, m[x])));
        cout << dp[getID(x, reg(y, m[x]))] << endl;
    }

    while (true) {
        int x, y;
        cin >> x >> y;
        debug(getID(x, reg(y, m[x])));
    }
    return 0;
}
