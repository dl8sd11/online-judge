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



const ll MAXB = MAXN*5;
ll bit[MAXB];
ll n,a[MAXN];

void init() {
    REP (i,MAXB) {
        bit[i] = 0;
    }
}

void add (ll pos,ll val) {
    pos += MAXN;
    for(;pos<=MAXB-1;pos+=-pos&pos) {
        bit[pos] += val;
    }
}

ll query(ll pos) {
    pos += MAXN;
    ll ret = 0;
    for (;pos>=1;pos-=pos&-pos) {
        ret += bit[pos];
    }
    return ret;
}


ll check(ll num) {
    init();
    ll pre = 0;
    ll tmp[MAXN];
    REP (i,n) {
        if (num >= a[i]) pre--;
        else pre++;
        tmp[i] = pre;
        add(pre,1);
    }
    pary(tmp,tmp+n);

    ll ret = 0;
    ll sum = -1;
    pre = 0;
    REP (i,n) {
        // debug(i,query(sum),sum);
        ret += query(sum);
        if (num >= a[i]) {
            pre--;
            sum--;
        } else {
            pre++;
            sum++;
        }
        add(pre,-1);
    }

    return ret;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    vector<ll> val;
    REP (i,n) {
        cin >> a[i];
        val.eb(a[i]);
    }
    if (n == 1) {
        cout << a[0] << endl;
        return 0;
    }
    sort(ALL(val));
    val.resize(unique(ALL(val))-val.begin());

    // debug(check(20));

    ll cb = n * (n+1) / 2;
    cb = cb/2 + 1;

    ll L = 0,R = SZ(val);
    while (L < R - 1) {
        ll mid = L+R>>1;
        ll ch = check(val[mid]);
        debug(val[mid],ch);
        if (ch >= cb) {
            R = mid;
        } else {
            L = mid;
        }
    }

    debug(L,R);
    cout << val[R] << endl;
    return 0;
}


/*
10
5 9 5 9 8 9 3 5 4 3

{3,3,4,4,4,4,4,4,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,5,8,8,8,8,8,8,8,8,8,8,8,8,8,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9,9}
*/