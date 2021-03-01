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
const ll MAXN = 101;

ll n,a[MAXN];
vector<ll> prime;
ll pid[MAXN],msk[MAXN];
ll dp[MAXN][1<<16];
ll tr[MAXN][1<<16];
/********** Good Luck :) **********/
int main()
{
    IOS();
    MEM(pid,-1);
    for (ll i=2;i<59;i++) {
        bool flag = false;
        for (ll j=2;j*j<=i;j++) {
            if (i % j == 0) {
                flag = true;
            }
        }
        if (!flag) {
            pid[i] = SZ(prime);
            prime.eb(i);
        }
    }
    
    for (ll i=2;i<59;i++) {
        for (ll j=2;j<=i;j++) {
            if (pid[j] != -1 && i % j == 0) {
                msk[i] |= (1<<pid[j]);
            }
        }
    }

    cin >> n;
    REP1 (i,n) {
        cin >> a[i];
    }

    MEM(dp,INF);
    dp[0][0] = 0;
    REP1 (i,n) {
        for (ll s=0;s<(1<<16);s++) {
            dp[i][s] = dp[i-1][s] + a[i] - 1;
            tr[i][s] = 1;
            for (ll j=2;j<59;j++) {
                ll val = dp[i-1][s^msk[j]] + abs(a[i]-j);
                if ((s & msk[j]) == msk[j] && val < dp[i][s]) {
                    dp[i][s] = val;
                    tr[i][s] = j;
                }
            }
        }
    }

    ll mn = 0;
    for (ll s=0;s<(1<<16);s++) {
        if (dp[n][s] < dp[n][mn]) {
            mn = s;
        }
    }

    vector<ll> ans;
    for (ll i=n;i>=1;i--) {
        ans.eb(tr[i][mn]);
        mn -= msk[tr[i][mn]];
    }

    reverse(ALL(ans));
    for (auto v : ans) {
        cout << v << " ";
    }
    cout << endl;
    return 0;
}
