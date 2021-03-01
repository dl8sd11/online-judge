#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
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
#define f first
#define s second
#define MX(a,b) a=max(a,b)
#define MN(a,b) a=min(a,b)
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
const int maxn = 2e5 + 5;

int n=maxn, zkw[maxn*2];

/*
    query: range max
    add: single change value
*/
void build () {
    for (int i=n-1; i>0; i--) {
        zkw[i] = min(zkw[i<<1], zkw[i<<1|1]);
    }
}

void chg (int x, int val) {
    for (zkw[x+=n]=val; x>1; x>>=1) {
        zkw[x>>1] = min(zkw[x], zkw[x^1]);
    }
}

int qry (int l, int r) {
    int ret = 0x3f3f3f3f3f3f3f3f;
    for (l+=n,r+=n; l<r; l>>=1, r>>=1) {
        if (l&1) {
            ret = min(ret, zkw[l++]);
        }
        if (r&1) {
            ret = min(ret, zkw[--r]);
        }
    }
    return ret;
}

signed main () {
    TIME(main);
    IOS();
    int n,k; cin>>n>>k;
    vector<int> a(n);
    for (int i = 0; i<n; ++i) {
        cin>>a[i];
    }
    vector<pll> ans(n);
    memset(zkw, 0x3f,sizeof zkw);
    for (int i = n-1; i>=0; --i) {
        int j = qry(max(0ll,a[i]-k),min(maxn-2,a[i]+k)+1);
        // debug(max(0,a[i]-k),min(maxn-2,a[i]+k)+1);
        debug(i,j,a[i]);
        if (j == 0x3f3f3f3f3f3f3f3f) {
            ans[i] = {a[i],a[i]};
        }else{
            ans[i] = ans[j];
            ans[i].s += a[i];
        }
        chg(a[i],i);
    }
    vector<ll> ps(maxn+1);
    for (int i = 0; i<n; ++i) {
        ps[ans[i].f] += ans[i].s;
    }
    for (int i = maxn-2; i>=0; --i) {
        ps[i] += ps[i+1];
    }
    int q; cin>>q;
    while (q--) {
        int x; cin>>x;
        if (x >= maxn) x = maxn-1;
        cout<<ps[x]<<endl;
    }
    return 0;
}
