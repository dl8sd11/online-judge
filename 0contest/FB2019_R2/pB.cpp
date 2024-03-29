#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<double,double> pdd;
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


const int MAXN = 5003;
int sz[MAXN],djs[MAXN];
void init(int n) {
    for (int i=0;i<=n;i++) {
        djs[i] = i;
        sz[i] = 1;
    }    
}

int fnd(int x) {
    return (x==djs[x])?x:djs[x]=fnd(djs[x]);
}

void uni(int x,int y) {
    if (sz[y=fnd(y)]>sz[x=fnd(x)]) {
        swap(x,y);
    }
    if (x == y) {
        return;
    }
    djs[y] = x;
    sz[x] = sz[x]+sz[y];
}


int t, n, m, x[10004], y[10004];
bool dp[MAXN][MAXN*2], tran[MAXN][MAXN*2], ans[MAXN];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> t;
    REP1 (testcase, t) {
        cout << "Case #" << testcase <<  ": ";
        cin >> n >> m;
        init(n);

        REP (i, m) {
            cin >> x[i] >> y[i];
            for (int j=x[i];j<=(x[i]+y[i])/2;j++) {
                uni(j,x[i]+y[i]-j);
            }
        }

        vector<pii> el;
        REP1 (i, n) {
            if (fnd(i) == i) {
                el.eb(i, sz[i]);
            }
        }


        MEM(dp, 0);
        dp[0][MAXN] = 1;
        REP (i, SZ(el)) {
            for (int j=MAXN-n;j<=MAXN+n;j++) {
                if (j - el[i].Y >= 0 && dp[i][j-el[i].Y]) {
                    dp[i+1][j] = true;
                    tran[i+1][j] = false;
                }
                if (j + el[i].Y < MAXN*2 && dp[i][j+el[i].Y]) {
                    dp[i+1][j] = true;
                    tran[i+1][j] = true;
                }
            }
        }

        int bst = 0;
        REP (i, MAXN*2) {
            if (dp[SZ(el)][i] && abs(i-MAXN) < abs(bst-MAXN)) {
                bst = i;
            }
        }

        RREP (i, SZ(el)-1) {
            int s = el[i].Y;
            REP1 (j, n) {
                if (fnd(j) == el[i].X) {
                    ans[j] = tran[i+1][bst];
                }
            }
            bst += (tran[i+1][bst] ? 1 : -1) * s;
        }

        REP1 (i, n) {
            cout << ans[i];
        }
        cout << endl;

        REP (i, m) {
            for (int j=x[i];j<=(x[i]+y[i])/2;j++) {
                assert(ans[j]==ans[x[i]+y[i]-j]);
            }
        }

    }
    return 0;
}
