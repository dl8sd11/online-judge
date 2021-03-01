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
const ll MAXN = 2001;

ll n,m;
ll deg[MAXN][MAXN];
bool pt[MAXN][MAXN],vis[MAXN][MAXN];
char opt[MAXN][MAXN];
ll dx[] = {-1,0,1,0};
ll dy[] = {0,1,0,-1};
bool valid(ll i,ll j) {
    return i >= 0 && i < n && j >= 0 && j < m;
}

void draw(pii x,pii y) {
    debug(x,y);
    if (x.X == y.X) {
        if (x.Y > y.Y) {
            swap(x,y);
        }
        opt[x.X][x.Y] = '<';
        opt[y.X][y.Y] = '>';
    } else {
        if (x.X > y.X) {
            swap(x,y);
        }
        opt[x.X][x.Y] = '^';
        opt[y.X][y.Y] = 'v';
    }
}
vector<pii> edge[MAXN][MAXN];

void dfs(pii cur) {
    debug(cur);
    vis[cur.X][cur.Y] = true;
    for (auto p : edge[cur.X][cur.Y]) {
        if (!vis[p.X][p.Y]) {
            vis[p.X][p.Y] = true;
            draw(cur,p);
            for (auto p2 : edge[p.X][p.Y]) {
                if (!vis[p2.X][p2.Y] && --deg[p2.X][p2.Y] == 1) {
                    dfs(p2);
                }
            }
        }
    }
}
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP (i,n) {
        REP (j,m) {
            cin >> opt[i][j];
            pt[i][j] = (opt[i][j] == '.');
        }
    }

    vector<pii> que;
    REP (i,n) {
        REP (j,m) {
            if (pt[i][j]) {
                REP (d,4) {
                    ll ci = i + dx[d];
                    ll cj = j + dy[d];
                    if (valid(ci,cj) && pt[ci][cj]) {
                        edge[i][j].eb(ci,cj);
                        deg[i][j]++;
                    }
                }
                if (deg[i][j] == 1) {
                    que.eb(i,j);
                }
            }
        }
    }

    for (auto p : que) {
        if (!vis[p.X][p.Y]) {
            dfs(p);
        }
    }

// #ifdef tmd
// REP (i,n) {
//         REP (j,m) {
//             cout << opt[i][j];
//         }
//         cout << endl;
//     }
// #endif
    REP (i,n) {
        REP (j,m) {
            if (opt[i][j] == '.') {
                cout << "Not unique" << endl;
                return 0;
            }
        }
    }
    REP (i,n) {
        REP (j,m) {
            cout << opt[i][j];
        }
        cout << endl;
    }
    return 0;
}
