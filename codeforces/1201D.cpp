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
const ll MAXN = 200005;

int n, m, k, q;
vector<int> trea[MAXN];
vector<int> safe;
ll dp[MAXN][2];

pair<int, int> trav(int pos, int idx) {
    int hd = trea[idx].front(), tl = trea[idx].back();
    return pii(abs(tl - pos) + abs(tl - hd), abs(hd - pos) + abs(tl - hd));
}

void upd(ll val, int pos, int idx) {
    val++;
    auto ptr = lower_bound(ALL(safe), pos); 
    int tL = (ptr == safe.end() ? (*prev(ptr)) : *ptr);
    int tR = (ptr == safe.begin() ? (*ptr) : (*prev(ptr)));

    pair<int,int> travL = trav(tL, idx);
    pair<int,int> travR = trav(tR, idx);

    travL.X += abs(tL - pos);
    travL.Y += abs(tL - pos);

    travR.X += abs(tR - pos);
    travR.Y += abs(tR - pos);

    dp[idx][0] = min({dp[idx][0], travL.X+val, travR.X+val});
    dp[idx][1] = min({dp[idx][1], travL.Y+val, travR.Y+val});
}


/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m >> k >> q;

    int mxN = 1;
    REP (i, k) {
        int r, c;
        cin >> r >> c;
        mxN = max(mxN, r);
        trea[r].eb(c);
    }
    n = mxN;

    REP (i, q) {
        int c;
        cin >> c;
        safe.eb(c);
    }

    REP1 (i, n) {
        sort(ALL(trea[i]));
    }
    sort(ALL(safe));

    MEM(dp, INF);

    int hd, ta;

    if (trea[1].empty()) {
        dp[1][0] = 0, dp[1][1] = 0;
        hd = 1, ta = 1;
    } else {
        pair<int, int> flay = trav(1, 1);
        dp[1][0] = flay.X, dp[1][1] = flay.Y;
        hd = trea[1].front(), ta = trea[1].back();
    }

    debug(safe);
    REP1 (i, n) {
        debug(trea[i]);
    }

    for (int i=1; i<n; i++) {
        if (trea[i+1].empty()) {
            dp[i+1][0] = dp[i][0] + 1;
            dp[i+1][1] = dp[i][1] + 1;
        } else {
            upd(dp[i][0], hd, i+1);
            upd(dp[i][1], ta, i+1);
            hd = trea[i+1].front(), ta = trea[i+1].back();
        }
    }
    REP1 (i, n) {
        debug(dp[i][0], dp[i][1]);
    }

    cout << min(dp[n][0], dp[n][1]) << endl;
    
    return 0;
}
