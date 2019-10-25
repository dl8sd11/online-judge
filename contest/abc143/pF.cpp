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
const ll MAXN = 1<<19;

int n;
vector<int> sz, val;

int bit[MAXN];
void add (int x, int val) {
    for (;x<MAXN; x+=-x&x) {
        bit[x] += val;
    }
}

int qry (int x) {
    int ret = 0;
    for (;x>0; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

int lbd (int x) {
    int res = 0, sum = 0;
    for (int h=18; h>=0; h--) {
        if (sum + bit[res+(1<<h)] < x) {
            sum += bit[res + (1<<h)];
            res += 1<<h;
        }
    }
    return res+1;
}
/********** Good Luck :) **********/
int main () {
    TIME(main);
    IOS();
    srand(time(0));
#ifdef tmd
    n = 1000;
#else
    cin >> n;
#endif

    REP (i, n) {
        int a;
        #ifdef tmd
            a = rand() % n + 1;
        #else
            cin >> a;
        #endif
        val.eb(a);
    }

    sort(ALL(val));
    int cnt = 1;
    for (int i=1; i<=SZ(val); i++) {
        if (i==SZ(val) || val[i]!=val[i-1]) {
            sz.emplace_back(cnt);
            cnt = 0;
        }
        cnt++;
    }
    sort(ALL(sz));
    debug(sz);

    REP1 (i, SZ(sz)) {
        add(i, i==1 ? sz[i-1] : sz[i-1] - sz[i-2]);
    }
    add(SZ(sz)+1, 1000000);


    REP1 (i, n) {
        vector<pii> op;
        int cnt = 0;
        while (qry(SZ(sz)-i+1) != 0) {
            int lw = qry(SZ(sz)-i+1);
            int l = lbd(lw), r = lbd(lw+1);

            int rem = i - (SZ(sz) - r + 1);
            add(r, -1);
            add(l, -1);
            add(l+rem, 1);
            // debug(l, r, lw);

            op.emplace_back(r, -1);
            op.emplace_back(l, -1);
            op.emplace_back(l+rem, 1);

            cnt++;

            #ifdef tmdd
            REP1 (i, SZ(sz)) {
                cout << qry(i) << " \n"[i==SZ(sz)];
            }
            #endif
        }
        for (auto p : op) {
            add(p.X, -p.Y);
        }

        #ifdef tmd
        int cnt2 = 0;
        priority_queue<int> pq;
        for (auto v : sz) {
            pq.emplace(v);
        }
        while (pq.size() >= i) {
            cnt2++;
            vector<int> cur;
            REP (j, i) {
                if (pq.top() > 1) {
                    cur.emplace_back(pq.top()-1);
                }
                pq.pop();
            }
            for (auto c : cur) {
                pq.emplace(c);
            }
        }

        if (cnt != cnt2) {
            debug(cnt, cnt2, i);
            return 0;
        }
        #endif
        cout << cnt << endl;
    }

    return 0;
}
