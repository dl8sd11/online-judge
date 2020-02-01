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
const ll MAXN = 400005;
const int MAXC = 20;

int n, a[MAXN];
ll tr[MAXC][MAXC];
ll dp[MAXC][1<<MAXC];

ll solve (int idx, int st) {
    if (dp[idx][st] != -1) {
        return dp[idx][st];
    } else if (idx == 0) {
        return dp[idx][st] = 0;
    } else {
        dp[idx][st] = INF;
        REP (i, MAXC) {
            if (st & (1<<i)) {
                ll cur = 0;
                REP (j, MAXC) {
                    if (j != i && (st & (1<<j))) {
                        cur += tr[i][j];
                    }
                }
                dp[idx][st] = min(dp[idx][st], solve(idx-1, st^(1<<i)) + cur);
            }
        }

        return dp[idx][st];
    }
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n;
    REP (i, n) {
        cin >> a[i];
        a[i]--;
    }

    {
        int cnt[MAXC] = {};
        RREP (i, n-1) {
            cnt[a[i]]++;
            REP (j, MAXC) {
                tr[a[i]][j] += cnt[j];
            }
        }
    }


    MEM(dp, -1);

    ll ans = solve(MAXC-1, (1<<MAXC)-1);


    cout << ans << endl;
    return 0;
}

/*
13
5 5 4 4 3 5 7 6 5 4 4 6 5

13
3 3 2 2 1 3 5 4 3 2 2 4 3
*/