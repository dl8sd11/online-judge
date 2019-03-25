#include <bits/stdc++.h>
using namespace std;
typedef pair<int, int> pii;
typedef pair<double,double> pdd;
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
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

const int MOD = 1000000007;
const int INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 200002;


int n,q,cnt;
int a[MAXN];
vector<int> val;
vector<pair<int,pii> > event;
const int sz = 2048;
int bl[MAXN];
struct Query {
    int l,r,md,id;
    bool operator < (const Query & b) const {
        if (bl[l] != bl[b.l]) {
            return l/sz < b.l/sz;
        } else if (bl[r] != bl[b.r]) {
            return r/sz < b.r/sz;
        } else {
            return md < b.md;
        }
        // return bl[l] == bl[b.l] ? (bl[r] == bl[b.r] ? (bl[r] & 1 ? md < b.md : md > b.md) : (bl[l] & 1 ? r < b.r : r > b.r)) : l < b.l;
    }
}query[MAXN];

int c[MAXN*2];
int oc[MAXN*2];

inline void add(int x) {
    assert(c[x] >= 0);
    oc[c[x]]--;
    c[x]++;
    oc[c[x]]++;
}

inline void dec(int x) {
    assert(c[x] >= 1);
    oc[c[x]]--;
    c[x]--;
    oc[c[x]]++;
}

int ans[MAXN];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> q;


    REP (i,n) {
        cin >> a[i];
        bl[i] = (i - 1) / sz + 1;
        val.eb(a[i]);
    }


    REP (qq,q) {
        int t;
        cin >> t;
        if (t == 1) {
            int l,r;
            cin >> l >> r;
            l--,r--;
            query[cnt]= {l,r,SZ(event),cnt};
            cnt++;
        } else {
            int p,x;
            cin >> p >> x;
            p--;
            event.eb(p,pii(-1,x));
            val.eb(x);
        }
    }

    sort(ALL(val));
    val.resize(unique(ALL(val))-val.begin());
    REP (i,n) {
        a[i] = lower_bound(ALL(val),a[i])-val.begin();
    }
    for (auto &E : event) {
        E.Y.Y = lower_bound(ALL(val),E.Y.Y)-val.begin();
    }



    sort(query,query+cnt);

    int L = 0,R = -1,T = 0;
    REP (i,cnt) {
        while (T < query[i].md) {
            int p = event[T].X;
            event[T].Y.X = a[p];
            if (p >= L && p <= R) {
                dec(a[p]);
                a[p] = event[T].Y.Y;
                add(a[p]);
            } else {
                a[p] = event[T].Y.Y;
            }
            T++;
        }

        while (T > query[i].md) {
            T--;
            int p = event[T].X;
            if (p >= L && p <= R) {
                dec(a[p]);
                a[p] = event[T].Y.X;
                add(a[p]);
            } else {
                a[p] = event[T].Y.X;
            }
        }

        while (R < query[i].r) {
            R++;
            add(a[R]);
        }

        while (L > query[i].l) {
            L--;
            add(a[L]);
        }

        while (R > query[i].r) {
            dec(a[R]);
            R--;
        }
        
        while (L < query[i].l) {
            dec(a[L]);
            L++;
        }
        REP1 (j,MAXN-1) {
            if (oc[j] <= 0) {
                ans[query[i].id] = j;
                break;
            }
        }
    }
    
    REP (i,cnt) {
        cout << ans[i] << endl;
    }
    return 0;
}