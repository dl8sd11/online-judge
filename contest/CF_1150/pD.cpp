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
const ll MAXN = 100003;

ll n,q;
string str;
string d[4];
ll dp[260][260][260],nxt[MAXN][30];

void upd(ll i,ll j,ll k) {
    dp[i][j][k] = INF;
    if (i > 0 && dp[i-1][j][k] != INF) {
        dp[i][j][k] = min(dp[i][j][k],nxt[dp[i-1][j][k]+1][d[1][i-1]-'a']);
    }
    if (j > 0 && dp[i][j-1][k] != INF) {
        dp[i][j][k] = min(dp[i][j][k],nxt[dp[i][j-1][k]+1][d[2][j-1]-'a']);
    }
    if (k > 0 && dp[i][j][k-1] != INF) {
        dp[i][j][k] = min(dp[i][j][k],nxt[dp[i][j][k-1]+1][d[3][k-1]-'a']);
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> q >> str;
    
    REP (c,26) {
        nxt[n][c] = INF;
        RREP (i,n-1) {
            if (str[i] == c+'a') {
                nxt[i][c] = i;
            } else {
                nxt[i][c] = nxt[i+1][c];
            }
        }
    }


    dp[0][0][0] = -1;
    while (q--) {
        char cmd,c;
        ll idx;
        cin >> cmd >> idx;
        if (cmd == '-') {
            d[idx].pop_back();
        } else {
            cin >> c;
            d[idx].push_back(c);
            if (idx == 1) {
                REP (i,SZ(d[2])+1) {
                    REP (j,SZ(d[3])+1) {
                        upd(SZ(d[1]),i,j);
                    }
                }
            } else if (idx == 2) {
                REP (i,SZ(d[1])+1) {
                    REP (j,SZ(d[3])+1) {
                        upd(i,SZ(d[2]),j);
                    }
                }
            } else if (idx == 3) {
                REP (i,SZ(d[1])+1) {
                    REP (j,SZ(d[2])+1) {
                        upd(i,j,SZ(d[3]));
                    }
                }
            }
        }
        if (dp[SZ(d[1])][SZ(d[2])][SZ(d[3])] == INF) {
            cout << "NO" << endl;
        } else {
            cout << "YES" << endl;
        }
    }
    return 0;
}
