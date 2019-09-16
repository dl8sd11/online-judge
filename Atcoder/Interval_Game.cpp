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
const ll MAXN = 100005;

int n;
vector<pii> pt;
vector<int> pl, pr;
bool vis[MAXN];
ll ans;

pii dis (int p, pii rng) {
    if (p < rng.X) {
        return {rng.X - p, rng.X};
    } else if (p > rng.Y) {
        return {p - rng.Y, rng.Y};
    } else {
        return {0, p};
    }
}

void solve (pii dt) {
    int lid = 0, rid = 0;
    int cur = dt.Y;
    ll sum = dt.X;
    REP (i, n-1) {
        while (lid<n && vis[pl[lid]]) {
            lid++;
        }
        while (rid<n && vis[pr[rid]]) {
            rid++;
        }
        debug(lid, rid);

        pii ldt = lid < n ? dis(cur, pt[pl[lid]]) : pii(-1, cur);
        pii rdt = rid < n ? dis(cur, pt[pr[rid]]) : pii(-1, cur);

        if (ldt.X > rdt.X) {
            sum += ldt.X;
            cur = ldt.Y;
            vis[pl[lid]] = true;
        } else {
            sum += rdt.X;
            cur = rdt.Y;
            vis[pr[rid]] = true;
        }
        
    }
    ans = max(ans, sum + abs(cur));
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n;
    REP (i, n) {
        int l, r;
        cin >> l >> r;
        pt.eb(l, r);
        pl.eb(i);
        pr.eb(i);
    }

    sort(ALL(pl), [](int a, int b) {
        if (pt[a].X != pt[b].X) {
            return pt[a].X > pt[b].X;
        } else {
            return pt[a].Y > pt[b].Y;
        }
    });

    sort(ALL(pr), [](int a, int b) {
        if (pt[a].Y != pt[b].Y) {
            return pt[a].Y < pt[b].Y;
        } else {
            return pt[a].X < pt[b].X;
        }
    });
    debug(pl);
    debug(pr);

    vis[pl.front()] = true;
    solve(dis(0, pt[pl.front()]));

    MEM(vis, 0);
    vis[pr.front()] = true;
    solve(dis(0, pt[pr.front()]));

    cout << ans << endl;
    return 0;
}
