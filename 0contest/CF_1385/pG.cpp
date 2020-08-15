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
const ll MAXN = 200005;

int t, n, a[2][MAXN], p[2][MAXN];

int djs[MAXN*2], sz[MAXN*2], wei[MAXN*2];

int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

void mrg (int x, int y) {
    x = fnd(x), y = fnd(y);
    if (sz[x] > sz[y]) {
        swap(x, y);
    }
    if (x == y) {
        return;
    }
    djs[x] = y;
    sz[y] += sz[x];
    wei[y] += wei[x];
}

pii app[MAXN];
int cnt[MAXN];
int main () {
    TIME(main);
    IOS();

    cin >> t;
    while (t--) {
        cin >> n;
        REP1 (i, n) {
            cnt[i] = 0;
        }

        REP (u, 2) {
            REP (i, n) {
                int num;
                cin >> num;
                a[u][i] = num;
                swap(app[num].X, app[num].Y);
                app[num].X = i*2 + u;
                cnt[num]++;
                
            }
        }

        bool flag = true;
        REP1 (i, n) {
            if (cnt[i] != 2) {
                flag = false;
            }
        }
        if (!flag) {
            cout << -1 << endl;
            continue;
        }

        REP (i, n*2) {
            djs[i] = i;
            sz[i] = 1;
            if (i&1) {
                wei[i] = 1;
            } else {
                wei[i] = 0;
            }
        }
        pary(wei, wei+n*2);

        REP1 (i, n) {
            int x = app[i].X >> 1, y = app[i].Y >> 1;
            if ((app[i].X ^ app[i].Y) & 1) {
                mrg(x<<1, y<<1);
                mrg(x<<1|1, y<<1|1);
            } else {
                mrg(x<<1, y<<1|1);
                mrg(x<<1|1, y<<1);
            }
        }

        int ans = 0;
        bool no_sol = false;

        set<int> gp;
        pary(wei, wei+n*2);
        pary(sz, sz+n*2);
        REP (i, n) {
            int f0 = fnd(i<<1), f1 = fnd(i<<1|1);
            debug(f0, f1);
            if (f0 == f1) {
                no_sol = true;
            }
            if (f0 == (i<<1)) {
                debug(i, wei[f0], wei[f1], sz[f0], sz[f1]);
                if (wei[f0] < wei[f1]) {
                    gp.insert(f0);
                    ans += wei[f0];
                } else {
                    gp.insert(f1);
                    ans += wei[f1];
                }
            }
        }

        if (no_sol) {
            cout << -1 << endl;
        } else {
            vector<int> vec;
            REP (i, n) {
                if (gp.count(fnd(i<<1|1))) {
                    vec.eb(i+1);
                }
            }
            debug(ans, vec);
            assert(SZ(vec) == ans);

            cout << SZ(vec) << endl;
            if (vec.empty()) {
                cout << endl;
            } else {
                for (int i=0; i<SZ(vec); i++) {
                    cout << vec[i] << " \n"[i==SZ(vec)-1];
                }
            }
        }

    }


    return 0;
}
