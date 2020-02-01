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
const ll MAXN = 100005;

ll mpow (ll bs, ll ep) {
    ll ret = 1;
    while (ep) {
        if (ep & 1) {
            ret = ret * bs % MOD;
        }
        bs = bs * bs % MOD;
        ep >>= 1;
    }
    return ret;
}

int t, n;
ll x[MAXN], fac[MAXN], pw[MAXN], rfac[MAXN];
vector<ll> st;
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    fac[0] = rfac[0] = pw[0] = 1;
    REP1 (i, MAXN-1) {
        fac[i] = fac[i-1] * i % MOD;
        rfac[i] = mpow(fac[i], MOD-2);
        pw[i] = pw[i-1] * 2 % MOD;
    }

    cin >> t;
    while (t--) {
        cin >> n;
        n *= 2;
        st.clear();

        ll ed = 0;
        REP (i, n) {
            ll d;
            cin >> d;
            st.eb(d);
            ed += d;
        }

        ed /= (n/2) + 1;
        int edcnt = 0;
        vector<ll> nw;

        for (auto v : st) {
            if (v == ed) {
                edcnt++;
            } else {
                nw.eb(v);
            }
        }

        if (edcnt < 2) {
            cout << 0 << endl;
            continue;
        }

        REP (i, edcnt-2) {
            nw.eb(ed);
        }
        st = nw;
        sort(ALL(st));
        debug(st);

        int ft = 0, bk = SZ(nw) - 1;
        ll ans = fac[n/2-1];
        while (ft < bk) {
            pair<int,int> head = {ft, bk};
            int cnt = 0;

            if (st[ft]+st[bk] != ed) {
                ans = 0;
            }
            while (ft<bk && st[ft] == st[head.X] && st[bk] == st[head.Y]) {
                cnt++;
                ft++, bk--;
            }

            ans = ans * rfac[cnt] % MOD;
            if (st[head.X] != st[head.Y]) {
                ans = ans * pw[cnt] % MOD;
            }
        }

        cout << ans << endl;

    }

    return 0;
}
