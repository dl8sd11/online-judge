#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
#define FOR(i, j, k, in) for (ll i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=k ; i-=in)
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
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif

template<class T> inline bool cmax(T &a, const T &b) { return b > a ? a = b, true : false; }
template<class T> inline bool cmin(T &a, const T &b) { return b < a ? a = b, true : false; }
template<class T> using MaxHeap = priority_queue<T>;
template<class T> using MinHeap = priority_queue<T, vector<T>, greater<T>>;

const ll MOD=1000000007;
const ll INF=0x3f3f3f3f3f3f3f3f;
const ll MAXN=1e5+5;
const ll MAXLG=__lg(MAXN)+2;

ll n,s;
ll solve(ll k) {
    ll sum = 0,dep = 0,b;
    for (b = 1;sum + b <= n;sum += b,b *= k) {
        dep++;
    }
    ll pre = n - sum, ret = n - sum;
    REP (i,dep) {
        b /= k;
        pre += b;
        ret += pre;
    }
    return ret;
}
ll ans[MAXN];
void build(ll k) {
    ll lev[MAXN],rem[MAXN],dep = 0;
    MEM(lev,0);
    MEM(rem,0);
    ll sum = 0,cur = 0;
    for (ll b = 1;sum + b <= n;sum += b,b *= k) {
        lev[dep] = b;
        if (dep > 0) {
            rem[dep] = lev[dep - 1] * (k+1) - lev[dep];
        }
        cur += lev[dep] * (dep + 1);
        dep++;
    }
    lev[dep] = n - sum;
    cur += lev[dep] * (dep + 1);
    rem[dep] = lev[dep - 1] * (k+1) - lev[dep];
    dep++;

    pary(lev,lev+dep);
    pary(rem,rem+dep);
    debug(cur);

    ll hd = 0, tl = dep;
    while (cur > s) {
        while (lev[tl] == 0) {
            tl--;
        }
        while (rem[hd] == 0) {
            hd++;
        }
        if (cur - (tl - hd) >= s) {
            cur -= tl - hd;
            lev[hd]++;
            lev[tl]--;
            rem[hd]--;
            rem[hd+1] += k + 1;
        } else {
            hd++;
        }
        debug(cur);
    }
    
    pary(lev,lev+dep);
    pary(rem,rem+dep);

    ll nid = 2;
    ll st[MAXN] = {};
    st[0] =  1;
    debug(tl);
    REP1 (i,tl) {
        st[i] = nid;
        REP (j,lev[i]) {
            ans[nid] = st[i-1] + j/(k+1);
            nid++;
        }
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> s;
    if (s > n * (n+1) / 2 || s < n + n -1) {
        cout << "No" << endl;
    } else {
        ll L = 1,R = n;
        while (L < R - 1) {
            ll mid = (L + R) >> 1;
            if (solve(mid) <= s) {
                R = mid;
            } else {
                L = mid;
            }
        }
        debug(L,R);
        build(L);

        cout << "Yes" << endl;
        for (ll i=2;i<=n;i++) {
            cout << ans[i] << " \n"[i==n];
        }
    }
    return 0;
}
