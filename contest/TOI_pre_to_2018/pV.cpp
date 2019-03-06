#include <bits/stdc++.h>
using namespace std;
typedef int ll;
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

int m,n,b[52],w[1003];

bool solve(int idx,int lst) {
    if (-1 == idx) {
        return true;
    }

    int st = 0;
    if (lst != -1 && w[idx] == w[idx+1]) {
        st = lst;
    }
    for (int i=st;i<m;i++) {
        if (b[i] < w[idx]) {
            continue;
        }
        b[i] -= w[idx];
        bool ret = solve(idx-1,i);
        b[i] += w[idx];
        if (ret) {
            return true;
        }
    }
    return false;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> m >> n;

    int tot = 0;
    REP (i,m) {
        cin >> b[i];
        tot += b[i];
    }
    REP (i,n) {
        cin >> w[i];
    }

    sort(w,w+n);
    pary(w,w+n);
    debug(tot);
    int ans = 0,sum = 0;
    REP (i,n) {
        if (sum + w[i] > tot) {
            break;
        }
        if (solve(i,-1)) {
            ans = i + 1;
        } else {
            break;
        }
        sum += w[i];
        
    }

    cout << ans << endl;
    return 0;
}
/* 海選加油 */
