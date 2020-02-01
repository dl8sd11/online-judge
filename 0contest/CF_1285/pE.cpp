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

typedef vector<pair<int,int>> vp;

vector<pair<pair<int,int>,int> > sid;
int t, n, k;
vp query;


bool use[MAXN];
vp build_big (vector<int> id) {
    memset(use, 0, sizeof(bool)*n);
    for (auto v : id) {
        use[v] = true;
    }

    vp vec, res;
    REP (i, n) {
        if (use[sid[i].Y]) {
            vec.eb(sid[i].X);
        }
    }

    // debug(vec);
    int lst = -1, far = -1;
    for (auto v : vec) {
        if (far != -1 && far < v.X) {
            res.eb(lst, far);
            lst = -1;
            far = -1;
        } 
        if (lst == -1) {
            lst = v.X;
        }
        far = max(far, v.Y);
    }
    if (far != -1) {
        res.eb(lst, far);
    }
    return res;
}

vp build (vector<int> id) {
    vp vec, res;
    for (auto v : id) {
        vec.eb(query[v]);
    }
    sort(ALL(vec));

    // debug(vec);
    int lst = -1, far = -1;
    for (auto v : vec) {
        if (far != -1 && far < v.X) {
            res.eb(lst, far);
            lst = -1;
            far = -1;
        } 
        if (lst == -1) {
            lst = v.X;
        }
        far = max(far, v.Y);
    }
    if (far != -1) {
        res.eb(lst, far);
    }
    return res;
}

/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> t;
    while (t--) {
        cin >> n;
        k = sqrt(n*__lg(n));
        debug(n, k);

        query.clear();
        sid.clear();
        REP (i, n) {
            int l, r;
            #ifdef tmd
            l = rand();
            r = rand();
            if (l > r ) {
                swap(l,r);
            }
            #else
            cin >> l >> r;
            #endif
            query.emplace_back(l, r);
            sid.eb(query.back(),i);
        }

        sort(ALL(sid));

        #ifdef tmd
        vector<int> aid;
        REP (i, n) {
            aid.eb(i);
        }
        vp x = build(aid);
        vp xx = build_big(aid);
        // debug(x);
        // debug(xx);
        assert(x == xx);
        #endif

        int ans = 0;
        REP (i, (n+k-1)/k) {
            vector<int> bid;
            REP (j, i*k) {
                bid.eb(j);
            }
            for (int j=(i+1)*k;j<n;j++) {
                bid.eb(j);
            }
            vp bg = build_big(bid);
            // debug(bid);
            // debug(bg);

            for (int j=i*k;j<min((i+1)*k,n); j++) {
                vector<int> ssid;
                for (int it=i*k;it<min((i+1)*k,n); it++) {
                    if (it != j) {
                        ssid.eb(it);
                    }
                }
                vp sm = build(ssid);

                int cur = SZ(bg);
                for (auto p : sm) {
                    int lid, rid;
                    int l = -1, r = SZ(bg);
                    while (l < r - 1) {
                        int mid = (l + r) >> 1;
                        if (bg[mid].Y >= p.X) {
                            r =mid;
                        } else {
                            l = mid;
                        }
                    }
                    lid = r;
                    l = -1, r = SZ(bg);
                    while (l < r - 1) {
                        int mid = (l + r) >> 1;
                        if (bg[mid].X <= p.Y) {
                            l =mid;
                        } else {
                            r = mid;
                        }
                    } 
                    rid= l;

                    cur -= rid - lid;
                }

                // debug(j, cur);
                ans = max(ans, cur);
            }
        }

        cout << ans << endl;
    }

    return 0;
}
