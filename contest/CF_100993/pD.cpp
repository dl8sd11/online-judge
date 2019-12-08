#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops,no-stack-protector")
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
const int MAXN = 500005;
// const int MAXN = 15;

int bit[MAXN];

void add (int x, int val) {
    for (x++;x<MAXN; x+=-x&x) {
        bit[x] += val;
    }
}

int qry (int x) {
    int ret = 0;
    for (x++; x>0; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

int qry (int l, int r) {
    return qry(r) - qry(l-1);
}

const int K = sqrt(500000+__lg(500000));
// const int K = 1;
int n, m, t[100005];
ll ans[K + 3];

inline int calc (int dif, int fri) {
    return (dif + fri - 1) / fri;
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();

    cin >> n >> m;
    for (int i=1; i<=n; i++) {
        cin >> t[i];
        add(t[i], 1);
        for (int j=1; j<=K; j++) {
            ans[j] += calc(t[i], j);
        }
    }

    for (int u=0; u<m; u++) {
        int p, v;
        cin >> p >> v;
        if (p == 1) {
            for (int j=1; j<=K; j++) {
                ans[j] += calc(t[v]+1, j) - calc(t[v], j);
            }
            add(t[v], -1);
            t[v]++;
            add(t[v], 1);
        } else if (p == 2) {
            for (int j=1; j<=K; j++) {
                ans[j] += calc(t[v]-1, j) - calc(t[v], j);
            }
            add(t[v], -1);
            t[v]--;
            add(t[v], 1);
        } else {
            if (v > K) {
                int bd = (MAXN-1) / v;
                int ret = 0;
                for (int i=1; i<=bd; i++) {
                    ret += i * qry((i-1)*v+1, i*v);
                    debug((i-1)*v+1, i*v, qry((i-1)*v+1, i*v));
                }
                ret += qry(v*bd+1, MAXN-1) * (bd + 1);

                cout << ret << endl;
            } else {
                cout << ans[v] << endl;
            }
        }

    }

    return 0;
}

/*
5 11
1 2 3 4 5
3 3

5 11
1 2 3 4 5
3 1
3 2
3 3
1 1
3 1
3 2
3 3
2 5
3 1
3 2
3 3
*/
