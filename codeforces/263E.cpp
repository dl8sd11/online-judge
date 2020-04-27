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
const ll MAXN = 1003;

struct Triangle {
    int n, m, k;
    vector<vector<int> > g;
    vector<vector<ll> > wt, t, wv, v, wh, h, d;
    Triangle (vector<vector<int> > gi, int ki) {
        g = gi;
        k = ki;
        n = gi.size();
        m = gi[0].size();


        wt.resize(n, vector<ll>(m));
        t.resize(n, vector<ll>(m));
        wv.resize(n, vector<ll>(m));
        v.resize(n, vector<ll>(m));
        wh.resize(n, vector<ll>(m));
        h.resize(n, vector<ll>(m));
        d.resize(n, vector<ll>(m));

        if (k > 0) {
            build();
        }
    }

    void buildD (int x, int y) {
        ll res = 0;
        for (int i=0; i<k; i++) {
            res += g[x-i][y-k+1+i];
        }
        d[x][y] = res;
    }

    void build () {
        debug("build pre", k);
        for (int j=k-1; j<=m-k; j++) {
            ll swv = 0, sv = 0;
            for (int i=0; i<k; i++) {
                swv += (i+1) * g[i][j];
                sv += g[i][j];
            }
            wv[k-1][j] = swv;
            v[k-1][j] = sv;
        }
    
        ll ti = 0, wti = 0;
        for (int i=0; i<k; i++) {
            for (int j=0; j<i+1; j++) {
                ti += g[i][k-1-j];
                wti += g[i][k-1-j] * (i+1-j);
            }
        }

        wt[k-1][k-1] = wti;
        t[k-1][k-1] = ti;
        buildD(k-1,k-1);

        for (int i=k; i<=n-k; i++) {
            ll twh = 0, th = 0, td = 0;
            for (int j=0; j<k; j++) {
                twh += g[i][j] * (j+1);
                th += g[i][j];
                td += g[i-j-1][j];
            }
            t[i][k-1] = t[i-1][k-1] + th - td;
            wt[i][k-1] = wt[i-1][k-1] + twh - t[i-1][k-1];
            buildD(i, k-1);
        }

        debug("main dish", k);
        for (int i=k-1; i<=n-k; i++) {
            for (int j=k-1; j<=m-k; j++) {
                if (i >= k) {
                    v[i][j] = v[i-1][j] + g[i][j] - g[i-k][j];
                    wv[i][j] = 1LL*k*g[i][j] + wv[i-1][j] - v[i-1][j];
                }
                if (i == k-1 || j == m-k) {
                    buildD(i,j);
                } else {
                    d[i][j] = d[i-1][j+1] - g[i-k][j+1] + g[i][j-k+1];
                }
                if (j >= k) {
                    wt[i][j] = wv[i][j] + wt[i][j-1] - t[i][j-1];
                    t[i][j] = t[i][j-1] + v[i][j] - d[i][j-1];
               }
            }
        }
    }


};

vector<vector<pii> > qry[4];
ll ans[MAXN][MAXN];

template<typename T>
vector<vector<T> > rotate (const vector<vector<T> > & vec) {
    vector<vector<T> > ret;
    ret.resize(vec[0].size(), vector<T>(vec.size()));

    int n = vec.size(), m = vec[0].size();
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            ret[m-j-1][i] = vec[i][j];
        }
    }
    return ret;
}

int main () {
    TIME(main);
    IOS();

    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int> > a;

    a.resize(n, vector<int>(m));
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            cin >> a[i][j];
        }
    }

    REP (i, 4) {
        qry[i].resize(n, vector<pii>(m,pii(-1,-1)));
    }

    for (int i=k-1; i<n-k+1; i++) {
        for (int j=k-1; j<m-k+1; j++) {
            qry[0][i][j] = {i,j};
            if (k>=2) {
                qry[1][i][j+1] = {i,j};
                qry[3][i+1][j] = {i,j};
            }
            if (k>=3) {
                qry[2][i+1][j+1] ={i,j};
            }
        }
    }

    vector<int> len = {k, k-1, k-2, k-1};
    REP (r, 4) {
        debug(r);
        Triangle dp(a, len[r]);

        debug(a);
        debug(dp.wt);
        for (int i=0; i<qry[r].size(); i++) {
            for (int j=0; j<qry[r][0].size(); j++) {
                if (qry[r][i][j].X != -1) {
                    if (qry[r][i][j] == pii(1,2)) {
                        debug(qry[r][i][j]);
                        debug(dp.wt[i][j]);
                    }
                    ans[qry[r][i][j].X][qry[r][i][j].Y] += dp.wt[i][j];
                }
            }
        }

        debug("rt");
        REP (i, 4) {
            qry[i] = rotate(qry[i]);
        }
        a = rotate(a);
        debug("rted");
    }

    pii bst = {k-1, k-1};
    for (int i=k-1; i<=n-k; i++) {
        for (int j=k-1; j<=m-k; j++) {
#ifdef tmd
            ll tmp = 0;
            for (int x=0; x<n; x++) {
                for (int y=0; y<m; y++) {
                    tmp += 1LL * a[x][y] * max(0, k-abs(i-x)-abs(j-y));
                }
            }
            
            if (tmp != ans[i][j]) {
                debug(i, j, ans[i][j], tmp);
            }
            assert(tmp == ans[i][j]);

#endif
            if (ans[i][j] >= ans[bst.X][bst.Y]) {
                bst = {i, j};
            }
        }
    }

    cout << bst.X+1 << " " << bst.Y+1 << endl;
    return 0;
}
