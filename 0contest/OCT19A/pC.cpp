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
const ll MAXN = 100005;

int t, n, m, djs[MAXN], edg_cnt[MAXN], ans[MAXN];
bool odd_deg[MAXN];
vector<int> edg[MAXN];

int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

void mrg (int x, int y) {
    x = fnd(x), y = fnd(y);
    djs[x] = y;
}

void make_even (int gid) {
    debug(odd_deg[gid]);
    if (odd_deg[gid]) {
        REP1 (i, n) {
            if (fnd(i) == gid && (SZ(edg[i]) & 1)) {
                ans[i] = 2;
                return;
            }
        }
    } else {
        int sec = -1;
        REP1 (i, n) {
            debug(i, gid, fnd(i), sec);
            if (gid == fnd(i)) {
                if (sec == -1) {
                    ans[i] = 2;
                    sec = edg[i].front();
                } else if (i == sec) {
                    ans[i] = 3;
                }
            }
        }
        debug(sec);
    }
}

void opt () {
    int mx = 0;
    REP1 (i, n) {
        mx = max(mx, ans[i]);
    }
    cout << mx << endl;
    REP1 (i, n) {
        cout << ans[i] << " \n"[i==n];
    }
}

bool check () {
    int cnt[4] = {};
    REP1 (i, n) {
        for (auto v : edg[i]) {
            if (ans[i] == ans[v] && i < v) {
                cnt[ans[i]]++;
            }
        }
    }

    REP1 (i, 3) {
        if (cnt[i] & 1) {
            return false;
        }
    }
    return true;
}


bool bf (int idx, int mx) {
    if (idx == n + 1) {
        return check();
    } else {
        REP1 (i, mx) {
            ans[idx] = i;
            if (bf(idx+1, mx)) {
                return true;
            }
        }
        return false;
    }
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> t;
    while (t--) {
        cin >> n >> m;
        REP1 (i, n) {
            djs[i] = i;
            ans[i] = 1;
            odd_deg[i] = 0;
            edg_cnt[i] = 0;
        }
        REP (i, m) {
            int u, v;
            cin >> u >> v;
            edg[u].emplace_back(v);
            edg[v].emplace_back(u);
            mrg(u, v);
        }

        if (n <= 10) {
            REP1 (i, 3) {
                if (bf(1, i)) {
                    break;
                }
            }
        } else {
            vector<int> gp;
            REP1 (i, n) {
                gp.emplace_back(fnd(i));
                edg_cnt[fnd(i)] += SZ(edg[i]);
                odd_deg[fnd(i)] |= SZ(edg[i]) & 1;
            }

            sort(gp.begin(), gp.end());
            gp.resize(unique(gp.begin(), gp.end()) - gp.begin());

            int odd_gp = 0, gd = -1, f_odd = -1;
            for (auto gid : gp) {
                edg_cnt[gid] /= 2;
                if (edg_cnt[gid] & 1) {
                    odd_gp++;
                    f_odd = gid;
                    if (odd_deg[gid]) {
                        gd = gid;
                    }
                }
            }

            if (odd_gp & 1) {
                debug(gd);
                if (gd == -1) {
                    make_even(f_odd);
                } else {
                    make_even(gd);
                }
            }
        }

        assert(check());
        opt();
        REP1 (i, n) {
            edg[i].clear();
        }
    }

    return 0;
}
