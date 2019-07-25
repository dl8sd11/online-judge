#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
typedef pair<double,double> pdd;
#define SQ(i) ((i)*(i))
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) int(i.size())
#define FOR(i, j, k, in) for (int i=j ; i<k ; i+=in)
#define RFOR(i, j, k, in) for (int i=j ; i>=k ; i-=in)
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
const int iNF = 0x3f3f3f3f;
// const ll MAXN = 

int phi[31][102];

ll mpow(ll base,ll ep,ll md) {
    ll ret = 1;
    while (ep > 0) {
        if (ep & 1) {
            ret = ret * base % md;
        }
        base = base * base % md;
        ep >>= 1;
    }
    return ret;
}

ll solve(ll k, ll idx,ll L) {
    ll md = phi[L][idx];
    debug(k, idx, md);
    if (k == 1) {
        return 3 % md;
    } else if (md == 1) {
        return 0;
    } else {
        return mpow(3, solve(k, idx+1, L), md);
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    REP1 (i, 30) {
        phi[i][0] = 1 << i;
        REP1 (j, 102) {
            int pv = phi[i][j-1], tmp = phi[i][j-1];
            // phi(p^n) = p^(n-1) * (p-1)
            phi[i][j] = 1;
            for (int k=2; k*k<=pv; k++) {
                if (tmp % k == 0) {
                    int bs = 1;
                    while (tmp % k == 0) {
                        bs *= k;
                        tmp /= k;
                    }
                    phi[i][j] *= bs/k * (k-1);
                }
            }

            if (phi[i][j] == 1) {
                break;
            }     
        }
    }

    int n, k , l;
    cin >> n;
    while (n--) {
        cin >> k >> l;
        cout << solve(k, 0, l) << endl;
    }


    return 0;
}
