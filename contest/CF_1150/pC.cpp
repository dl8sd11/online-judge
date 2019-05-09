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
const ll MAXN = 200005;

ll n,cnt1,cnt2;
vector<ll> prime;
/********** Good Luck :) **********/
int main()
{
    IOS();
    for (ll i=2;i<MAXN*2;i++) {
        if (i > 2 && (i&1^1)) {
            continue;
        }
        bool np = false;
        for (ll j=2;j*j<=i;j++) {
            if (i%j == 0) {
                np = true;
            }
        }
        if (!np) {
            prime.eb(i);
        }
    }
    cin >> n;
    REP (i,n) {
        ll d;
        cin >> d;
        if (d == 1) {
            cnt1++;
        } else {
            cnt2++;
        }
    }
    vector<ll> ans;
    ll sum = 0;
    for (auto p : prime) {
        if (cnt1 == 0 && cnt2 == 0) {
            break;
        }
        ll tw = min(cnt2,(p-sum)>>1);
        REP (i,tw) {
            ans.eb(2);
        }
        cnt2 -= tw;
        sum += tw * 2;

        ll on = min(cnt1,p-sum);
        REP (i,on) {
            ans.eb(1);
        }
        cnt1 -= on;
        sum += on; 
    }

    debug(ans);
    ll c1 = 0,c2 = 0;
    REP (i,n) {
        if (ans[i] == 1) {
            c1++;
        } else {
            c2++;
        }
    }


    REP (i,SZ(ans)) {
        cout << ans[i] << " \n"[i==SZ(ans)-1];
    }
    return 0;
}
