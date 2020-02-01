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
const ll MAXN = 100005;

ll n,m;
ll b[MAXN],a[MAXN],c[MAXN];
vector<pii> one[1<<10];
pair<ll,pii> two[1<<10];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP (i,n) {
        ll f;
        cin >> f;
        REP (j,f) {
            ll d;
            cin >> d;
            d--;
            b[i] += (1LL << d);
        }
    }

    REP (i,m) {
        cin >> c[i];
        ll r;
        cin >> r;
        REP (j,r) {
            ll d;
            cin >> d;
            d--;
            a[i] += (1LL << d);
        }
        one[a[i]].eb(c[i],i);
    }

    for (ll i=0;i<(1LL<<10);i++) {
        sort(ALL(one[i]));
        two[i].X = INF;
    }

    for (ll i=0;i<(1LL<<10);i++) {
        for (ll j=0;j<(1LL<<10);j++) {
            if (i == j) {
                if (SZ(one[i]) >= 2 && two[i].X > one[i][0].X + one[i][1].X) {
                    two[i].X = one[i][0].X + one[i][1].X;
                    two[i].Y = pii(one[i][0].Y,one[i][1].Y);
                }
            } else if (!one[i].empty() && !one[j].empty()) {
                if (two[i|j].X > one[i][0].X + one[j][0].X) {
                    two[i|j].X = one[i][0].X + one[j][0].X;
                    two[i|j].Y = pii(one[i][0].Y,one[j][0].Y);
                }
            }
        }
    }

    ll ans = 0;
    ll pr = INF;
    pii buy = {0,1};

    for (ll i=0;i<(1LL<<10);i++) {
        if (two[i].X != INF) {
            ll cnt = 0;
            REP (j,n) {
                if ((b[j] & i) == b[j]) {
                    cnt++;
                }
            }
            if (cnt > ans) {
                ans = cnt;
                pr = two[i].X;
                buy = two[i].Y;
            } else if (cnt == ans) {
                if (pr > two[i].X) {
                    pr = two[i].X;
                    buy = two[i].Y;
                }
            }
            debug(cnt,two[i],i);
        }
    }

    cout << buy.X + 1 << " " << buy.Y + 1 << endl;


    return 0;
}
