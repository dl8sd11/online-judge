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

const ll M = 1000000007;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const ll MAXN = 3003; 
const ll C = 880301;

ll mpow(ll base,ll ep) {
    ll ret = 1;
    while (ep > 0) {
        if (ep & 1) {
            ret = ret * base % M;
        }
        base = base * base % M;
        ep >>= 1;
    }
    return ret;
}

int n;
ll ans, pre[MAXN], inv[MAXN];
char c;
string s;

ll getHS (int l, int r) {
    ll ret = pre[r + 1] - pre[l];
    if (ret < 0) {
        ret += M;
    }
    ret = ret * inv[l] % M;
    return ret;
}

int id[MAXN][MAXN];
int vis[MAXN][MAXN];
int dp[MAXN][MAXN];
int hs_val[MAXN][MAXN];
int cnt[MAXN];
/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();
    {
        TIME(PRE);
        cin >> n;
        REP (i, MAXN) {
            inv[i] = mpow(C, i * (M - 2) % (M - 1));
        }
        ll bs = 1;
        REP (i, n) {
            cin >> c;
            s += c;

            pre[i+1] = (pre[i] + c * bs) % M;
            bs = bs * C % M;

            REP (j, i+1) {
                hs_val[i-j+1][cnt[i-j+1]++] = getHS(j, i);
            }
        }

        {
            TIME(srt_unq);
            REP1 (i, n) {
                sort(hs_val[i], hs_val[i]+cnt[i]);
                cnt[i]  = unique(hs_val[i], hs_val[i]+cnt[i]) - hs_val[i];
            }
        }

        {
            TIME(lbd);
            int l, r, len, h, m;
            REP (i, n) {
                REP (j, i+1) {
                    len = i-j+1;
                    l = -1, r = cnt[len]-1;
                    h = getHS(j, i);
                    while (l < r - 1) {
                        m = (l + r) >> 1;
                        if (hs_val[len][m] >= h) {
                            r = m;
                        } else {
                            l = m;
                        }
                    }
                    id[j][i] = r;
                }
            }
        }
    }

    MEM(vis, -1);
    REP (i, n) {
        ll sum = 0;
        string l4 = s.substr(max(0, i-3),min(i+1, 4));
        bool ban = (l4 == "0011" || l4 == "0101" || l4 == "1110" || l4 == "1111");
        // debug(l4, ban);
        for (int j=i; j>=0; j--) {
            int &v = vis[i-j+1][id[j][i]];
            if (v == -1) {
                v = i;
                ll cur = 0;
                for (int k=1; k<=min(i-j+1, 4); k++) {
                    // debug(i, j, k);
                    if (k != 4 || !ban) {
                        // debug(i, j, k);
                        cur += (i-k-j + 1 == 0) ? 1 : dp[j][i-k];
                        cur %= MOD;
                    }
                }
                dp[j][i] = cur;
                ans = (ans + cur) % MOD;
            } else {
                dp[j][i] = dp[v-(i-j)][v];
            }
        }

        cout << ans << endl;
    }


    return 0;
}
