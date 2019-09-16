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
const ll MAXN = 5003;

int n, p[MAXN], f[MAXN], ps[MAXN], opt[MAXN];
bool vp[MAXN*2], vf[MAXN];
bool wab (int x) {
    REP (i, x) {
        if (ps[i] >= f[n-x+i]) {
            return false;
        }
    }

    return true;
}

bool sab (int rem, bool vb = false) {
    int idx = 0, cnt = 0;
    REP (i, n) {
        if (!vp[i]) {
            while (idx < n && (vf[idx] || f[idx] <= ps[i])) {
                idx++;
            }

            if (f[idx] > ps[i]) {
                if (vb) {
                    debug(idx, i);
                }
                cnt++;
            }
            idx++;
        }
    }

    assert(cnt <= rem);
    return cnt >= rem;
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n;
    REP (i, n) {
        cin >> p[i];
        ps[i] = p[i];
    }

    REP (i, n) {
        cin >> f[i];
    }

    sort(ps, ps+n);
    sort(f, f+n);

    int ans = 0, r = n+1;
    while (ans < r - 1) {
        int md = (ans + r) >> 1;
        if (wab(md)) {
            ans = md;
        } else {
            r = md;
        }
    }

    debug(ans);

    int sum = 0;
    REP (i, n) {
        REP (j, n) {
            if (!vp[j] && ps[j] == p[i]) {
                vp[j] = true;
                break;
            }
        }

        vector<int> ls, wn;
        REP (j, n) {
            if (!vf[j]) {
                if (f[j] > p[i]) {
                    wn.eb(j);
                } else {
                    ls.eb(j);
                }
            }
        }
        debug(ls, wn);

        {
            int l = -1;
            r = SZ(wn);
            // check win
            while (l < r - 1) {
                int md = (l + r) >> 1, fc = -1;
                fc = wn[md];

                vf[fc] = true;
                if (sab(ans - sum - (f[fc] > p[i]))) {
                    l = md;
                } else {
                    r = md;
                }
                vf[fc] = false;
            }            
            debug(l, r, ans, sum, i);
            pary(vf, vf+n);
            pary(vp, vp+n);

            if (l != -1) {
                int j = wn[l];
                vf[j] = true;
                sum += f[j] > p[i];
                debug(f[j], sum);
                sab(ans - sum, true);
                opt[i] = f[j];
                debug(opt[i]);
                continue;
            }
        }
        {
            int l = -1;
            r = SZ(ls);
            // check lose
            while (l < r - 1) {
                int md = (l + r) >> 1, fc = -1;
                fc = ls[md];

                vf[fc] = true;
                if (sab(ans - sum - (f[fc] > p[i]))) {
                    l = md;
                } else {
                    r = md;
                }
                vf[fc] = false;
            }            

            debug(l, i, sum);
            assert(l != -1);
            if (l != -1) {
                int j = ls[l];
                vf[j] = true;
                sum += f[j] > p[i];
                debug(f[j], sum);
                sab(ans - sum, true);
                opt[i] = f[j];
                debug(opt[i]);
                continue;
            }
        }

        
    }
     
    REP (i, n) {
        cout << opt[i] << " \n"[i==n-1];
    }
    return 0;
}
