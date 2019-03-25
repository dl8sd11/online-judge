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
const ll MAXN = 10003;



vector<ll> edge[MAXN];

bool vis[MAXN];
ll yp[MAXN];
bool dfs(ll nd) {
    for (auto v : edge[nd]) {
        if (vis[v]) {
            continue;
        }
        vis[v] = true;
        if (yp[v] == -1 || dfs(yp[v])) {
            yp[v] = nd;
            return true;
        }
    }
    return false;
}
/********** Good Luck :) **********/
int main()
{
    IOS();

    // REP (n,16) {
    //     REP (m,16) {
        ll n,m;
            cin >> n >> m;
            if (n > m) {
                swap(n,m);
            }

        if (n == 1) {
            if (m%6 <= 3) {
                cout << m-m%6 << endl;
            } else {
                cout << m-(6-m%6) << endl;
            }
            return 0;
        }

        if (m > 16) {
            if ((n &1) && (m & 1)) {
                cout << n * m -1 << endl;
            } else {
                cout << n * m << endl;
            }
            return 0;
        }

            function<ll (ll,ll)> id =[&](ll x,ll y) {
                return x*m + y;
            };
            REP (i,MAXN) {
                edge[i].clear();
            }
            REP (i,n) {
                REP (j,m) {
                    REP(a,n) {
                        REP(b,m) {
                            if ((i+j)&1 && abs(i-a)+abs(j-b) == 3) {
                                edge[id(i,j)].eb(id(a,b));
                            }
                        }
                    }
                }
            }

            ll ans = 0;
            MEM(yp,-1);
            REP (i,n) {
                REP (j,m) {
                    if ((i+j)&1) {
                        MEM(vis,0);
                        // debug(i,j);
                        ans += dfs(id(i,j));
                    }
                }
            }

            // cout << setw(6) <<  ans * 2;
            cout << (ans*2) << endl;
    //     }
    //     cout << endl;
    // }
    return 0;
}
