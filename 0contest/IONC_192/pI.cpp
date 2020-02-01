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
const ll MAXN = 100005; 

int n, W, k, w[21], dp[21][MAXN];
vector<int> p[21], pre[21];
deque<int> deq[MAXN];

ll tran(int did, int kid,int cw) {
    int pos = deq[cw%w[kid]][did];
    if (cw == pos) {
        return dp[kid-1][pos];
    }
    return dp[kid-1][pos] + pre[kid][(cw-pos-1)/w[kid]];
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> W >> k;
    REP1 (i, k) {
        cin >> w[i];
    }

    REP1 (i, n) {
        int pc, tp;
        cin >> pc >> tp;
        p[tp].eb(pc);
    }

    REP1 (i,k) {
        sort(ALL(p[i]));
        reverse(ALL(p[i]));
        int sum = 0;
        for (auto v : p[i]) {
            sum += v;
            pre[i].eb(sum);
        }
    }

// dp[k][w] = dp[k-1][w - c[i]*j] + p[i]*j
    REP1 (i, k) {
        if (SZ(p[i]) == 0) {
            REP (j, W+1) {
                dp[i][j] = dp[i-1][j];
            }
            continue;
        }
        REP (j, MAXN) {
            deq[j].clear();
        }
        REP (j, W+1) {
            int pr = dp[k-1][j];
            while (SZ(deq[j%w[i]]) && pr >= dp[k-1][deq[j%w[i]].back()] + p[i][0]) {
                deq[j%w[i]].pop_back();
            }
            deq[j%w[i]].eb(j);
            while (SZ(deq[j%w[i]]) && j-deq[j%w[i]].front() > w[i]*SZ(p[i])) {
                deq[j%w[i]].pop_front();
            }
            while (SZ(deq[j%w[i]]) >= 2 && tran(0,i,j) <= tran(1,i,j)) {
                deq[j%w[i]].pop_front();
            }
            dp[i][j] = tran(0,i,j);
        }
    }

    cout << dp[k][W] << endl;


    return 0;
}
