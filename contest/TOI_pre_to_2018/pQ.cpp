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

int n;
int R[1001][1001],G[1001][1001],B[1001][1001],cv[1001][1001];
map<int,int> cnt;
int hs(int r,int g,int b) {
    return (r<<16) + (g<<8) + b;
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n;
    REP (s,n) {
        int xa,xb,ya,yb,r,g,b;
        cin >> xa >> ya >> xb >> yb >> r >> g >> b;
        if (xa > xb) {
            swap(xa,xb);
        }
        if (ya > yb) {
            swap(ya,yb);
        }
        for (int i=xa;i<xb;i++) {
            for (int j=ya;j<yb;j++) {
                R[i][j] += r;
                G[i][j] += g;
                B[i][j] += b;
                cv[i][j]++;
            }
        }

    }

    for (int i=0;i<=1000;i++) {
        for (int j=0;j<=1000;j++) {
            if (cv[i][j]) {
                R[i][j] = (R[i][j]+cv[i][j]-1)/cv[i][j];
                G[i][j] = (G[i][j]+cv[i][j]-1)/cv[i][j];
                B[i][j] = (B[i][j]+cv[i][j]-1)/cv[i][j];
                assert(R[i][j] >= 0 && R[i][j] <= 255);
                assert(G[i][j] >= 0 && G[i][j] <= 255);
                assert(B[i][j] >= 0 && B[i][j] <= 255);
                cnt[hs(R[i][j],G[i][j],B[i][j])]++;
            }
        }
    }

    pii ans;

    for (auto it : cnt) {
        if (it.X != 0 && it.Y > ans.X) {
            ans.X = it.Y;
            ans.Y = it.X;
        }
    }
    

    int ab = ans.Y & ((1<<8)-1);
    ans.Y >>= 8;
    int ag = ans.Y & ((1<<8)-1);
    ans.Y >>= 8;
    int ar = ans.Y & ((1<<8)-1);

    cout << ar << " " << ag << " " << ab << endl;

    return 0;
}
/* 海選加油 */
