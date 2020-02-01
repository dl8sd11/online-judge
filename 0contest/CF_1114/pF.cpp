#include <bits/stdc++.h>
#pragma GCC optimize("O3,unroll-loops,no-stack-protector")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
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
const ll MAXN = 4e5 + 7;

int n,q,bit[64][2][MAXN];
void add(ll pos,ll val,ll idx,bool ed) {
    for (;pos<=n;pos+=-pos&pos) {
        bit[idx][ed][pos] += val;
    }
}
ll query(ll pos,ll idx,bool ed) {
    ll ret = 0;
    for (;pos>0;pos-=-pos&pos) {
        ret += bit[idx][ed][pos];
    }
    return ret;
}

void radd(ll l,ll r,ll val,ll idx) {
    add(l,val,idx,0);
    add(r+1,-val,idx,0);
    add(l,val*(l-1),idx,1);
    add(r+1,-val*(r),idx,1);
}

ll rquery(ll pos,ll idx) {
    if (pos == 0) {
        return 0;
    }
    return pos*query(pos,idx,0) - query(pos,idx,1);
}
ll rquery(ll l,ll r,ll idx) {
    return rquery(r,idx) - rquery(l-1,idx);
}
const ll MAXC = 300;
ll prime[100],pptr;
bool sieve[MAXC];

void linear_sieve() {
    for (ll i=2;i<MAXC;i++) {
        if (!sieve[i]) {
            prime[pptr++] = i;
        }
        for (ll j=0;j<pptr&&prime[j]*i<MAXC;j++) {
            sieve[prime[j]*i] = true;
        }
    }    
}

ll mpow(ll a, ll b)
{
    ll ans = 1;
    while(b) {
        if(b & 1) ans = (ans * a) % MOD;
        a = (a * a) % MOD;
        b >>= 1;
    }
    return ans;
}

char cmd[8];
ll a;
ll l,r,val;
/********** Good Luck :) **********/
int main()
{
    IOS();
    linear_sieve();
    cin >> n >> q;
    REP1 (i,n) {
        cin >> a;
        REP (j,pptr) {
            ll cnt = 0;
            while (a % prime[j] == 0) {
                a /= prime[j];
                cnt++;
            }
            if (cnt) {
                radd(i,i,cnt,j);
            }
        }
    }

    while (q--) {
        cin >> cmd;
        if (cmd[0] == 'M') {
            cin >> l >> r >> val;
            REP (j,pptr) {
                ll cnt = 0;
                while (val % prime[j] == 0) {
                    val /= prime[j];
                    cnt++;
                }
                if (cnt) {
                    radd(l,r,cnt,j);
                }
            }   
        } else {
            ll ret=1;
            cin >> l >> r;
            REP (j,pptr) {
                ll p = prime[j];
                ll qu = rquery(l,r,j);
                if (qu) {
                    ret = (ret * (p-1) % MOD * mpow(p,qu-1)) % MOD;
                }
            }

            cout << ret << endl;
        }
    }
    return 0;
}
