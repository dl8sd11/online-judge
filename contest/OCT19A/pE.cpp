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

const int MAXN = 500005;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;

int n, k;
vector<int> a;

int lst[MAXN], dp[MAXN];
namespace Check {
    int LIS (const vector<int> &v) {
        memset(lst, iNF, (SZ(v)+1)*sizeof(int));
        lst[0] = -1;
        int mx = 0;
        REP (i, SZ(v)) {
            int L = 0, R = SZ(v);
            while (L < R - 1) {
                int mid = (L + R) >> 1;
                if (v[i] < lst[mid]) {
                    R = mid;
                } else {
                    L = mid;
                }
            }
            int idx = R;//upper_bound(lst, lst+SZ(v), v[i]) - lst;
            dp[i] = idx;
            lst[idx] = v[i];
            if (dp[i] > dp[mx]) {
                mx = i;
            }
        }
        return dp[mx];
    }
}

namespace Ans {
    vector<int> b;
    int len;
    void upd (const vector<int> &v) {
        int cur = Check::LIS(v);
        #ifdef tmd
            cout << "Sub: " << cur << endl;
        #endif
        if (cur > len) {
            b = v;
            len = cur;
        }
    }
}

namespace Smallk {
    vector<int> gen () {
        debug("test");
        vector<int> ft;
        vector<vector<int> > bk;
        int lnv = -2;
        REP (i, n) {
            if (a[i] > (k-1)/2) {
                if (i != lnv + 1) {
                    bk.push_back({a[i]});
                } else {
                    bk.back().emplace_back(a[i]);
                }
                lnv = i;
            }
        }

        vector<int> perm;
        REP (i, SZ(bk)) {
            perm.emplace_back(i);
        }
        REP (i, (k-1)/2) {
            ft.emplace_back(i+1);
        }

        while (double(clock())/CLOCKS_PER_SEC < 2.9) {
            vector<pair<int,int> > opp;
            REP (i, 1) {
                int u = rand() % SZ(bk);
                int v = rand() % SZ(bk);
                opp.emplace_back(u, v);
                swap(perm[u], perm[v]);
            }

            int Res = 0;
{
            memset(lst, iNF, (n+1)*sizeof(int));
            lst[0] = -1;
            int mx = 0;
            int cnt = 0, bkid = 0;
            REP (i, n) {
                int V = 0;
                if (i < (k-1)/2) {
                    V = i+1;
                } else {
                    V = bk[perm[bkid]][cnt];
                    cnt++;
                    if (cnt == bk[perm[bkid]].size()) {
                        bkid++;
                        cnt = 0;
                    }
                }

                int L = 0, R = n;
                while (L < R - 1) {
                    int mid = (L + R) >> 1;
                    if (V < lst[mid]) {
                        R = mid;
                    } else {
                        L = mid;
                    }
                }
                int idx = R;
                dp[i] = idx;
                lst[idx] = V;
                if (dp[i] > dp[mx]) {
                    mx = i;
                }
            }
            Res = dp[mx];

}
            int lis = Res;
            if (lis < Ans::len) {
                for (int i=SZ(opp)-1;i>=0;i--) {
                    swap(perm[opp[i].first], perm[opp[i].second]);
                }
            } else {
                Ans::len = lis;
            }
        }

        REP (i, SZ(bk)) {
            ft.insert(ft.end(), bk[perm[i]].begin(), bk[perm[i]].end());
        }
        Ans::b = ft;
        return ft;
    }
}

/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
    srand(time(0));

#ifdef tmdd
    n = 500000;
    k = 5000;
    a.resize(n);
    REP1 (i, n) {
        a[i-1] = i;
    }
    random_shuffle(a.begin(), a.end());
#else
    cin >> n >> k;

    a.resize(n);
    REP (i, n) {
        cin >> a[i];
    }
#endif

    Ans::upd(a);
    Ans::upd(Smallk::gen());
#ifdef tmdd
    cout << "Result: " << Ans::len << endl;
#else
    REP (i, n) {
        cout << Ans::b[i] << " \n"[i==n-1];
    }
#endif
    return 0;
}
