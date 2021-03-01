#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
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
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const int MOD[] = {1000000007,1000000009,20020607,1000000087};
const ll C[] = {880301,91,107,10103};
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll MAXN = 1000006;
const ll MAXT = 4;
ll mpow(int idx,int ep) {
    ll ret = 1,base = C[idx];
    while (ep > 0) {
        if (ep & 1) {
            ret = ret * base % MOD[idx];
        }
        base = base * base % MOD[idx];
        ep >>= 1;
    }
    return ret;
}

int n,m,pw[MAXN][4];
vector<int> hsv[MAXN];
vector<vector<int>> srt_hs;
vector<int> edge[MAXN];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    srt_hs.reserve(n);
    REP1 (i,n) {
        hsv[i] = vector<int>(MAXT);
    }

    REP (j,MAXT) {
        pw[0][j] = 1;
    }
    REP1 (i,MAXN-1) {
        REP (j,MAXT) {
            pw[i][j] = pw[i-1][j] * C[j] % MOD[j];
        }
    }

    REP (i,m) {
        int u,v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
        REP (j,MAXT) {
            hsv[u][j] = ll(hsv[u][j] + pw[v][j]) % MOD[j];
            hsv[v][j] = ll(hsv[v][j] + pw[u][j]) % MOD[j];
        }
    }

    debug("HI");
    REP1 (i,n) {
        srt_hs.eb(hsv[i]);
    }
    sort(ALL(srt_hs));
    pary(hsv+1,hsv+1+n);
    debug(srt_hs);
    ll ans = 0;
    REP1 (i,n) {
        ans += upper_bound(ALL(srt_hs),hsv[i]) - lower_bound(ALL(srt_hs),hsv[i]) - 1;
        for (auto v : edge[i]) {
            bool bf = true;
            bool af = true;
            REP (j,MAXT) {
                bf &= (hsv[i][j] == hsv[v][j]);
                af &= (ll(hsv[i][j] + pw[i][j]) % MOD[j] == ll(hsv[v][j] + pw[v][j]) % MOD[j]);
            }
            if (bf) {
                ans--;
            } 
            if (af) {
                ans++;
            }
        }
        debug(ans);
    }

    debug(ans);
    cout << ans/2 << endl;
    return 0;
}
