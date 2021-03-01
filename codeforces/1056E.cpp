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

const ll INF = 0x3f3f3f3f3f3f3f3f;
const int iNF = 0x3f3f3f3f;
const int MAXN = 1000006;
const int R = 3;
const ll MOD[] = {1000000007, 1000000009, 20020607};
ll C[R + 2];
string s, t;
int cnt[2];
ll pre[5][MAXN];
ll inv[R+2][MAXN];

vector<array<ll, R> > h[2];
bool check (int s0, int s1) {
    h[0].clear(), h[1].clear();

    int sz[2] = {s0, s1};
    int l = 0;
    for (auto c : s) {
        int cur = c - '0';
        array<ll, R> cur_hash;

        REP (r, R) {
            cur_hash[r] = pre[r][l+sz[cur]] - pre[r][l] + MOD[r];
            if (cur_hash[r] > MOD[r]) {
                cur_hash[r] -= MOD[r];
            }
            cur_hash[r] = cur_hash[r] * inv[r][l] % MOD[r];
        }

        l += sz[cur];
        h[cur].eb(cur_hash);
    }
    assert(l == SZ(t));

    debug(SZ(h[0]), SZ(h[1]));
    REP (d, 2) {
        REP1 (i, SZ(h[d]) - 1) {
            debug(h[d][i-1][0], h[d][i][0]);
            if (h[d][i] != h[d][i-1]) {
                return false;
            }
        }
    }

    return h[0].front() != h[1].front();
}

ll mpow(ll base,ll ep, ll r) {
    ep = ep % (MOD[r] - 1);
    ll ret = 1;
    while (ep > 0) {
        if (ep & 1) {
            ret = ret * base % MOD[r];
        }
        base = base * base % MOD[r];
        ep >>= 1;
    }
    return ret;
}

/********** Good Luck :) **********/
int main()
{
    TIME(main);
    IOS();
    srand(time(0));
    REP (i, 3) {
        C[i] = rand() % 10000 + 256;
    }

    {
        TIME(INV);
        REP (r, R) {
            REP (i, MAXN) {
                inv[r][i] = mpow(C[r], (MOD[r]-2)*i, r);
            }
        }
    }

    cin >> s >> t;

    REP (i, 3) {
        ll bs = 1;
        REP (j, SZ(t)) {
            pre[i][j+1] = (pre[i][j] + bs * t[j]) % MOD[i];
            bs = bs * C[i] % MOD[i];
        }
        // pary(pre[i]+1, pre[i]+SZ(t)+1);
    }

    {
        TIME(s1);
        for (auto c : s) {
            cnt[c - '0']++;
        }

        if (cnt[1] > cnt[0]) {
            for (auto &c : s) {
                c = ((c - '0') ^ 1) + '0';
            }
            swap(cnt[0], cnt[1]);
        }
    }
    debug(s);
    debug(cnt[0], cnt[1]);

    {
        TIME(calc);
        int ans = 0;
        for (int sz0=1; sz0*cnt[0]<=SZ(t); sz0++) {
            int sz1 = (SZ(t) - sz0*cnt[0]) / cnt[1];
            if (sz1 > 0 && sz0 * cnt[0] + sz1 * cnt[1] == SZ(t)) {
                debug(sz0, sz1);
                bool ret = check(sz0, sz1);
                ans += ret;
                debug(ret);
            }
        }
        cout << ans << endl;
    }

    return 0;
}
