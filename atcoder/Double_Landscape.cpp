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
const ll MAXN = 1003;

ll n,m,posx[MAXN*MAXN],posy[MAXN*MAXN];
ll a[MAXN],b[MAXN];
bool visx[MAXN][MAXN],visy[MAXN][MAXN];
ll cnt;

void vx(ll y) {
    REP (i,n) {
        if (!visy[i][y]) {
            if (visx[y][i]) {
                cnt++;
            }
            visy[i][y] = true;
        }
    }
}

void vy(ll x) {
    REP (i,m) {
        if (!visx[i][x]) {
            if (visy[x][i]) {
                cnt++;
            }
            visx[i][x] = true;
        }
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;

    MEM(posx,-1);
    MEM(posy,-1);
    REP (i,n) {
        cin >> a[i];
        posx[a[i]] = i;
    }
    REP (i,m) {
        cin >> b[i];
        posy[b[i]] = i;
    }

    ll ans = 1;
    for (ll i=n*m;i>=1;i--) {
        if (posx[i] != -1 && posy[i] != -1) {
            vx(posy[i]);
            vy(posx[i]);
            cnt--;
        } else if (posx[i] != -1) {
            ll cur = 0;
            REP (j,m) {
                cur += visy[posx[i]][j];
            }
            ans = ans * cur % MOD;
            debug(cur);
            vy(posx[i]);
            cnt--;
        } else if (posy[i] != -1) {
            ll cur = 0;
            REP (j,n) {
                cur += visx[posy[i]][j];
            }
            ans = ans * cur % MOD;
            debug(cur);
            vx(posy[i]);
            cnt--;
        } else {
            debug(cnt);
            ans = ans * (cnt--) % MOD;
        }
    }

    cout << ans << endl;
    return 0;
}
