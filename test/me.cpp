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

const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll MAXN = 5e5 + 7;

ll dp[MAXN],n,k,val[MAXN],pre[MAXN],f[MAXN],c[MAXN];
deque<ll> line;

ll solve(ll i,ll x) {
    return c[x]+2*i*x;
}

ll inter(ll i,ll j) {
    if ((c[j]-c[i] > 0) ^ (i-j > 0)) {
        if (c[i] < c[j]) {
            swap(i,j);
        }
        return -(c[i]-c[j]+2*i-2*j-1)/(2*i-2*j);
    } else {
        return (c[j]-c[i])/(2*i-2*j);
    }
}

inline ll p(ll idx) {
    return idx>=0 ? pre[idx] : 0;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> k;
    REP (i,n) {
        cin >> val[i];
        pre[i] = val[i];
        if (i) {
            pre[i] += pre[i-1];
        }
    }

    REP (i,n) {
        dp[i] = -INF;
    }
    dp[n] = 0;
    c[n] = -p(n-1)-n*n;
    line.emplace_back(n);
    for (ll i=n-1;i>=0;i--) {
        f[i] = (i+1)*p(n-1)-i*p(i-1)-i*i;
        while (line.size()>1 && line.front()-i >k) {
            line.pop_front();
        }
        while (line.size()>1 && solve(i,line[0]) <= solve(i,line[1])) {
            line.pop_front();
        }
        dp[i] = f[i]+solve(i,line.front());

        c[i]=(p(i-1)-p(n-1))*i-p(i-1)-i*i+dp[i];
        debug(i,c[i]);
        if (SZ(line) > 1) {
            debug(inter(i,line.back()),line[SZ(line)-2]-k-1,inter(line.back(),line[SZ(line)-2]));
        }
        while (SZ(line) > 1 && inter(i,line.back()) >= max(line[SZ(line)-2]-k-1,inter(line.back(),line[SZ(line)-2]))) {
            line.pop_back();
        }
        line.emplace_back(i);
        debug(line);
    }  

    pary(dp,dp+n);
    pary(c,c+n);
    cout << dp[0] << endl;
    return 0;
}
