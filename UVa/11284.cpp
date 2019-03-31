#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pii;
#define MEM(a, b) memset(a, (b), sizeof(a))
#define SZ(i) ll(i.size())
#define FOR(i, j, k, in) for (ll i=j ; i<(k) ; i+=in)
#define RFOR(i, j, k, in) for (ll i=j ; i>=(k) ; i-=in)
#define REP(i, j) FOR(i, 0, j, 1)
#define REP1(i,j) FOR(i, 1, j+1, 1)
#define RREP(i, j) RFOR(i, j, 0, 1)
#define ALL(_a) _a.begin(),_a.end()
#define mp make_pair
#define pb push_back
#define eb emplace_back
#define X first
#define Y second
#ifdef tmd1
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
const ll MAXN = 51;


ll T,n,m,p;
ll dis[MAXN][MAXN];
ll price[MAXN];
ll store[13];
ll dp[1<<13][13];
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> T;
    while (T--) {
        cin >> n >> m;

        //initailize distance
        REP (i,n+1) {
            REP (j,n+1) {
                if (i != j) {
                    dis[i][j] = INF;
                } else {
                    dis[i][j] = 0;
                }
            }
        }

        REP (i,m) {
            ll u,v,a1,a2;
            char c;
            cin >> u >> v >> a1 >> c >> a2;
            dis[u][v] = min(dis[u][v],a2+a1*100);
            dis[v][u] = min(dis[v][u],a2+a1*100);
        }
        
        REP (k,n+1) {
            REP (i,n+1) {
                REP (j,n+1) {
                    dis[i][j] = min(dis[i][j],dis[i][k]+dis[k][j]);
                }
            }
        }

        cin >> p;
        store[0] = 0;
        price[0] = 0;
    
        REP1 (i,p) {
            ll a1,a2;
            char c;
            cin >> store[i] >> a1 >> c >> a2;
            price[i] = a1*100 + a2;;
        }


        ll ans = 0;
        REP (st,1<<(p+1)) {
            REP (i,p+1) {
                dp[st][i] = -INF;
            }
        }
        dp[1][0] = 0;
        REP (st,1<<(p+1)) {
            REP (g,p+1) {
                if ((st>>g)&1) {
                    REP (t,p+1) {
                        if (t != g && ((st>>t)&1)) {
                            dp[st][g] = max(dp[st][g],dp[st-(1<<g)][t]+price[g]-dis[store[t]][store[g]]);
                        }
                    }
                }
                ans = max(ans,dp[st][g]-dis[store[g]][0]);
            }
        }

        if (ans > 0) {
            cout << "Daniel can save $" << ans/100 << "." << setw(2) << setfill('0') <<ans%100 << endl;
        } else {
            cout << "Don't leave the house" << endl;
        }
    }
    return 0;
}


/*
1
8 357
5 2 9.30
8 6 8.78
8 1 4.40
8 6 0.42
0 2 3.27
7 7 6.12
6 1 7.09
2 4 9.33
6 0 8.16
7 7 8.26
5 1 8.10
0 1 1.49
0 3 9.67
2 1 3.36
2 2 2.28
4 6 3.57
8 2 7.08
1 1 4.90
3 8 5.30
4 7 6.66
0 8 8.01
1 0 4.08
6 7 2.98
7 7 0.13
6 4 0.63
0 5 6.69
6 7 6.29
4 2 1.95
6 8 4.51
6 3 1.23
5 7 7.52
8 7 3.37
2 0 5.01
0 2 8.28
2 8 1.77
0 3 9.04
5 2 7.45
6 3 2.98
7 7 9.68
8 0 5.57
6 1 3.95
0 5 5.30
1 6 9.42
7 4 8.52
1 0 6.95
7 6 9.01
8 6 7.38
6 1 7.90
5 4 3.35
7 8 0.98
6 3 4.54
2 7 7.60
1 6 1.23
2 2 7.70
0 1 2.20
2 7 5.34
8 6 3.63
0 1 5.90
8 0 6.23
6 4 2.17
8 0 2.47
0 1 8.85
4 7 1.44
2 1 9.15
6 2 0.42
5 6 1.52
3 7 8.18
2 6 8.15
7 5 6.69
1 3 5.47
8 8 6.62
3 0 3.77
7 0 3.35
2 5 7.76
3 1 8.74
0 3 3.01
4 8 0.94
4 8 7.89
1 0 1.93
8 5 4.55
3 3 9.63
1 5 1.08
0 6 8.44
5 6 9.97
0 0 2.03
5 3 0.14
5 4 0.09
3 7 2.23
1 1 7.37
3 3 5.25
8 5 5.64
6 3 7.04
8 6 9.76
8 4 7.97
5 5 7.48
0 5 6.99
3 4 5.53
4 5 6.07
2 2 3.05
0 8 2.24
7 8 4.00
3 2 2.85
7 2 1.55
6 2 5.76
2 3 3.57
1 5 6.14
6 0 1.33
8 4 7.62
4 5 0.31
5 6 8.73
0 1 3.58
3 1 9.60
4 3 4.80
4 0 5.46
7 2 0.00
4 1 8.57
2 2 5.93
2 0 4.18
3 0 7.29
4 5 1.02
7 1 4.19
3 3 2.69
6 0 4.73
0 0 3.85
2 7 4.06
2 5 1.32
0 4 8.97
7 3 2.31
7 4 9.00
7 3 2.58
5 2 9.50
4 5 8.79
8 7 5.49
1 8 7.71
0 1 9.83
7 6 7.23
5 7 2.29
5 3 2.99
6 7 7.76
0 3 9.58
3 6 0.64
8 8 7.51
8 5 5.51
3 8 0.80
4 8 6.49
3 5 0.25
5 3 7.88
2 4 5.50
6 0 2.57
7 3 6.66
5 8 5.53
5 2 7.42
5 5 3.07
3 5 2.00
8 0 1.71
6 8 6.25
2 6 3.48
5 6 9.74
2 8 2.20
7 5 0.54
1 1 2.53
8 7 3.56
4 2 8.98
1 3 1.16
7 8 3.52
1 5 9.01
0 5 8.91
4 4 6.71
5 6 1.20
4 5 4.53
5 1 7.11
2 4 5.33
7 7 7.95
8 1 5.16
5 4 9.24
5 7 6.61
7 6 1.08
1 6 0.15
4 4 9.05
3 4 7.20
6 1 8.65
3 3 7.28
5 1 1.67
0 2 0.46
3 4 4.67
2 1 9.91
3 2 2.11
5 1 7.18
7 4 7.67
6 8 0.14
0 6 0.28
8 0 7.27
6 1 5.40
8 3 0.83
5 0 0.11
0 3 8.76
4 6 2.45
0 3 1.92
8 0 0.37
7 3 7.15
3 1 1.29
7 4 5.01
8 5 9.58
8 3 0.89
8 7 8.46
5 8 3.38
2 7 7.19
7 2 7.88
1 0 0.35
6 2 6.84
3 2 7.34
6 1 6.15
8 6 6.61
7 8 6.31
0 1 7.98
8 8 5.03
2 1 3.91
2 2 3.65
5 4 1.06
5 1 8.32
3 7 6.54
5 7 9.00
5 4 7.47
3 4 3.17
6 2 7.62
5 6 7.08
2 5 7.61
8 7 6.21
1 8 9.55
7 3 5.55
7 3 2.93
8 2 4.44
1 5 1.52
7 7 3.03
8 8 7.99
4 8 9.21
0 6 0.86
3 8 4.10
0 8 6.05
3 2 4.31
1 2 6.99
4 2 3.70
4 8 8.57
0 4 1.77
0 5 1.76
5 6 4.34
5 1 0.26
4 3 5.22
7 8 8.84
6 0 1.27
6 5 5.37
4 2 5.81
2 2 7.32
3 2 7.59
0 0 4.62
5 4 1.50
0 2 8.36
0 8 1.12
1 8 3.90
4 6 0.14
1 6 1.50
8 8 8.21
3 5 2.45
2 6 5.10
3 3 1.73
7 2 0.96
0 0 6.75
5 6 4.89
1 7 2.63
4 6 2.50
5 3 3.64
8 6 7.58
5 4 3.16
1 8 0.60
0 3 7.41
0 1 7.87
3 4 1.28
3 2 8.75
7 0 3.29
0 0 4.71
2 3 0.79
5 7 0.80
1 3 1.38
4 1 8.28
7 2 9.80
5 6 9.47
0 7 5.43
0 0 2.61
3 3 3.80
3 7 4.23
7 3 8.45
8 5 6.10
7 7 2.90
3 6 5.55
8 1 2.75
1 4 2.26
2 3 7.83
8 6 8.79
1 2 1.37
4 8 2.84
6 4 9.60
5 0 7.07
5 1 5.62
7 5 8.90
4 5 3.13
6 8 8.40
2 0 3.94
0 0 5.51
5 7 5.44
6 6 5.84
0 1 5.14
7 1 0.28
2 4 6.63
5 0 5.43
8 7 9.81
2 3 1.63
3 2 3.79
5 5 4.87
5 5 7.88
4 0 4.66
1 1 2.36
4 0 8.34
2 1 6.51
8 7 4.67
1 8 3.27
1 2 2.95
7 4 4.35
7 2 0.28
1 2 5.87
0 1 6.46
8 1 6.12
5 4 7.81
0 1 3.21
3 0 9.50
5 3 7.54
7 0 3.30
6 5 7.77
8 5 2.72
1 4 1.53
2 1 9.56
3 2 9.00
0 8 7.04
5 0 1.44
8 1 4.16
0 7 6.18
6 4 1.28
8 8 8.40
0 6 5.83
7 4 8.78
5 5 3.82
6 0 4.40
0 7 0.28
6 0 8.69
8 6 7.10
0 2 1.25
0 0 4.31
5 8 8.69
11
3 6.10
1 0.64
5 3.61
8 6.20
3 6.61
6 4.34
6 0.90
3 2.60
6 9.28
3 3.81
7 4.68
*/