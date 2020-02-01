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
// const ll MAXN = 

ll n,cntl,cntr,invl,invr;
vector<bool> o,t;

ll ans = INF;
/********** Good Luck :) **********/
int main()
{
#ifndef tmd
    freopen("balance.in","r",stdin);
    freopen ("balance.out","w",stdout);
#endif
    cin >> n;
    REP (i,n*2) {
        bool b;
        cin >> b;
        o.pb(b);
        if (i < n) {
            cntl += b;
            if (!b) {
                invl += cntl;
            }
        } else {
            cntr += b;
            if (!b) {
                invr += cntr;
            }
        }
    }
    debug(invl,invr);

    ans = abs(invl-invr);

    // clone var
    t = o;
    ll tcl = cntl, tcr = cntr;
    ll til = invl, tir = invr;

    // 0 1 in middle
    ll il = n-1,ir = n;
    ll sum = 0;

    for (ll i=1;i<=min(n-cntl,cntr);i++) {
        while (t[il]) {
            il--;
        }
        while (!t[ir]) {
            ir++;
        }

        //swap two elements
        sum++;
        sum += n-1-il;
        sum += ir-n;
        til += n-1-il;
        tir += ir-n;
        til -= tcl;
        tir -= n-tcr;
        tcl++;
        tcr--;
        swap(t[il],t[n-1]);
        swap(t[ir],t[n]);
        swap(t[n-1],t[n]);

        debug(til,tir);
        debug(sum+abs(til-tir));
        ans = min(ans,sum+abs(til-tir)); 
    }

    // clone var
    t = o;
    tcl = cntl, tcr = cntr;
    til = invl, tir = invr;

    // 1 0 in middle
    il = n-1,ir = n;
    sum = 0;
    for (ll i=1;i<=min(n-cntr,cntl);i++) {
        while (!t[il]) {
            il--;
        }
        while (t[ir]) {
            ir++;
        }

        //swap two elements
        sum++;
        sum += n-1-il;
        sum += ir-n;
        til -= n-1-il;
        tir -= ir-n;
        tcl--;
        tcr++;
        til += tcl;
        tir += n-tcr;
        swap(t[il],t[n-1]);
        swap(t[ir],t[n]);
        swap(t[n-1],t[n]);

        debug(til,tir);
        debug(sum+abs(til-tir));
        ans = min(ans,sum+abs(til-tir)); 
    }

    cout << ans << endl;
    return 0;
}
