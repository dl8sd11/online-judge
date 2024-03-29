#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const int MAXN = 100005;
const int K = 300; 
int n, m, id[MAXN], cnt;
vector<int> edge[MAXN];
unordered_set<int> small[MAXN];
bitset<MAXN> big[K], tmp, tmp2;

int szidx[MAXN];
vector<pii> sz;
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP (i, m) {
        int u, v;
        cin >> u >> v;
        edge[u].eb(v);
        edge[v].eb(u);
    }
    

    REP1 (i, n) {
        edge[i].resize(unique(ALL(edge[i]))-edge[i].begin());
        sz.eb(SZ(edge[i]), i);
        if (SZ(edge[i]) > K) {
            id[i] = ++cnt;
            for (auto v : edge[i]) {
                big[cnt][v] = true;
            }
        } else {
            for (auto v : edge[i]) {
                small[i].insert(v);
            }
        }
    }
    sort(ALL(sz));
    int idd = 0;
    for (auto p : sz) {
        szidx[p.Y] = idd++;
    }

    ll ans = 0;
    REP1 (i, n) {
        if (SZ(edge[i]) > K) {
            for (auto v : edge[i]) {
                if (szidx[v] > szidx[i]) {
                    tmp = big[id[v]];
                    tmp2 = big[id[i]];
                    ans += (tmp & tmp2).count();
                }
            }
        } else {
            for (auto v : edge[i]) {
                if (SZ(edge[v]) > K) {
                    for (auto w : edge[i]) {
                        ans += big[id[v]][w];
                    }
                } else if (szidx[v] > szidx[i]) {
                    for (auto w : edge[i]) {
                        ans += small[v].count(w);
                    }
                }
            }
        }
    }

    cout << ans/3 << endl;
    return 0;
}
