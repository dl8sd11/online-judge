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
const ll MAXN = 200005;
const ll C = 880301;
const ll P = 1000000009;
int n;
string t, a[MAXN];
ll t_hash[MAXN];
map<ll, ll> cnt;

ll mpow(ll base,ll ep) {
    ll ret = 1;
    while (ep > 0) {
        if (ep & 1) {
            ret = ret * base % P;
        }
        base = base * base % P;
        ep >>= 1;
    }
    return ret;
}

ll inv[MAXN];
int occ[MAXN][2];
/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();

    cin >> t;
    ll bs = 1;
    {
        TIME(hash_t);
        REP1 (i, SZ(t)) {
            inv[i-1] = mpow(bs, P - 2);
            t_hash[i] = (t_hash[i-1] + bs * t[i-1]) % P;
            bs = bs * C % P;
        }
    }
    cin >> n;
    REP (i, n) {
        cin >> a[i];
    }

    {
        TIME(srt_a);
        sort(a, a+n, [&](string s1, string s2) {
            return SZ(s1) < SZ(s2);
        });
    }

    int tbl[MAXN];
    {
        TIME(match);
        REP (i, n) {
            int hd = i;
            int tbl_sz = 0;
            {
                // TIME(FLL);
                while (i < n && SZ(a[i]) == SZ(a[hd])) {
                    ll sum = 0;
                    for (auto c : a[i]) {
                        sum = (sum * C + c) % P;
                    }
                    tbl[tbl_sz++] = sum;
                    i++;
                }
                i--;
            }

            {
                // TIME(USE);
                {
                    // TIME(srt);
                    sort(tbl, tbl+tbl_sz);
                }
                bs = 1;
                for (int j=0; j<=SZ(t)-SZ(a[hd]); j++) {
                    ll cur = (t_hash[j + SZ(a[hd])] - t_hash[j] + P) % P;
                    cur = inv[j] * cur % P;

                    // auto p = equal_range(tbl, tbl+tbl_sz, cur);

                    // int cnt_cur = p.Y - p.X;
                    int cnt_cur = 0;
                    if (cnt_cur) {
                        occ[j][0] += cnt_cur;
                        occ[j + SZ(a[hd])][1] += cnt_cur;
                    }
                    bs = C * bs % P; 
                }
            }
        }
    }

    ll ans = 0;

    {
        TIME(calc);
        REP (i, SZ(t)) {
            ans += ll(occ[i][0]) * occ[i][1];
        }
    }

    cout << ans << endl;
    return 0;
}

/*
aaabacaa
2
a
aa

5


aaabacaa
4
a
a
a
b


33
*/