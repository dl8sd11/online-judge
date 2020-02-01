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


vector<ll> s1,s2;
set<ll> s;

ll c1,c2;
void dfs(ll idx) {
    if (idx == 4) {
        s.insert(c1);
        return;
    }
    ll tc1 = c1,tc2 = c2;
    vector<ll> ts1 = s1;
    vector<ll> ts2 = s2;
    if (idx & 1) {
        REP (i,SZ(s2)) {
            c2 -= s2[i];
            c1 += s2[i];
            s1.push_back(s2[i]);
            s2.erase(s2.begin()+i);
            dfs(idx+1);
            c1 = tc1;
            c2 = tc2;
            s1 = ts1;
            s2 = ts2;
        }
    } else {
        REP (i,SZ(s1)) {
            c2 += s1[i];
            c1 -= s1[i];
            s2.push_back(s1[i]);
            s1.erase(s1.begin()+i);
            dfs(idx+1);
            c1 = tc1;
            c2 = tc2;
            s1 = ts1;
            s2 = ts2;
        }
    }
}
/********** Good Luck :) **********/
int main()
{
    freopen("backforth.in","r",stdin);
    freopen ("backforth.out","w",stdout);

    IOS();

    REP (i,10) {
        ll tmp;
        cin >> tmp;
        s1.eb(tmp);
    }

    REP (i,10) {
        ll tmp;
        cin >> tmp;
        s2.eb(tmp);
    }

    c1 = 1000,c2 = 1000;
    dfs(0);
    debug(s);

    cout << SZ(s) << endl;
    return 0;
}
