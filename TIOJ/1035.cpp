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
const ll MAXN = 50002;

string sa,sb;
vector<complex<double> > a,b,ret;
vector<ll> res;

const double pi = acos(-1);
void FFT(vector<complex<double>> &v,ll n,ll t) {
    assert(SZ(v) == n);
    // debug(v,n);
    if (n == 1) {
        return;
    }
    vector<complex<double> > o(n>>1),e(n>>1);
    REP (i,n>>1) {
        o[i] = v[i<<1];
        e[i] = v[i<<1|1];
    }
    FFT(o,n>>1,t),FFT(e,n>>1,t);

    complex<double> w1(cos(2*pi/n),t*sin(2*pi/n)),w0(1,0);
    for (ll i=0;i<(n>>1);i++,w0=w0*w1) {
        // debug(i,SZ(v),SZ(o),SZ(e));
        v[i] = o[i] + w0*e[i];
        v[i+(n>>1)] = o[i] - w0*e[i];
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> sa >> sb;
    reverse(ALL(sb));
    ll sum = 1;
    while (sum < SZ(sa) + SZ(sb)) {
        sum <<= 1;
    }

    a.resize(sum);
    b.resize(sum);
    ret.resize(sum);
    res.resize(sum);
    REP (i,10) {
        REP (j,sum) {
            a[j] = 0;
            b[j] = 0;
        }
        REP (j,SZ(sa)) {
            a[j] = (sa[j] == 'a'+i);
        }
        REP (j,SZ(sb)) {
            b[j] = (sb[j] == 'a'+i);
        }
        FFT(a,sum,1);
        FFT(b,sum,1);
        REP (j,sum) {
            ret[j] = a[j] * b[j];
        }
        FFT(ret,sum,-1);
        REP (j,sum) {
            res[j] += (ret[j].real()+0.1)/sum;
        }
    }

    ll ans = 0;
    REP (j,sum) {
        ans = max(ans,res[j]);
    }

    cout << ans << endl;
    return 0;

}
