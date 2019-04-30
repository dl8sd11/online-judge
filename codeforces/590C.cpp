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
const ll INF = 0x3f3f3f3f;
const ll MAXN = 1003;

ll n,m,st[MAXN][MAXN],dis[MAXN][MAXN][4];
bool vis[MAXN][MAXN];
ll dx[] = {-1,0,1,0};
ll dy[] = {0,1,0,-1};
ll pth[4],ans;
/********** Good Luck :) **********/
int main()
{
    IOS();
    cin >> n >> m;
    REP (i,n) {
        REP (j,m) {
            char c;
            cin >> c;
            if (c >= '1' && c <= '3') {
                st[i][j] = c - '0';
            } else if (c == '#') {
                st[i][j] = -1;
            }
        }
    }

    REP (i,n) {
        REP (j,m) {
            REP (k,4) {
                dis[i][j][k] = INF;
            }
        }
    }

    REP1 (c,3) {
        MEM(vis,0);
        queue<pii> bfs;
        REP (i,n) {
            REP (j,m) {
                if (st[i][j] == c) {
                    bfs.emplace(i,j);
                    vis[i][j] = true;
                    dis[i][j][c] = 0;
                }
            }
        }

        while (bfs.size()) {
            pii cur = bfs.front();
            bfs.pop();
            REP (i,4) {
                ll cx = cur.X + dx[i],cy = cur.Y + dy[i];
                if (cx >= 0 && cx < n && cy >= 0 && cy < m && !vis[cx][cy] && st[cx][cy] >= 0) {
                    vis[cx][cy] = true;
                    dis[cx][cy][c] = dis[cur.X][cur.Y][c] + 1;
                    bfs.emplace(cx,cy);
                }
            }
        }

        // print distance
        // REP (i,n) {
        //     REP (j,m) {
        //         if (dis[i][j][c] == INF) {
        //             cout << "-1 ";
        //         } else {
        //             cout << dis[i][j][c] << " ";
        //         }
        //     }
        //     cout << endl;
        // }
    }

    ans = INF;
    REP1 (i,3) {
        pth[i] = INF;
    }
    debug(ans);
    REP (i,n) {
        REP (j,m) {
            ans = min(ans,dis[i][j][1]+dis[i][j][2]+dis[i][j][3]-2);
            REP1 (c,3) {
                ll sum = 0;
                REP1 (d,3) {
                    if (d != c) {
                        sum += dis[i][j][d];
                    }
                }
                pth[c] = min(pth[c],sum);
            }
        }
    }

    debug(ans);
    pary(pth+1,pth+4);
    REP1 (i,3) {
        ll sum = 0;
        REP1 (j,3) {
            if (i != j) {
                sum += pth[j];
            }
        }
        ans = min(sum-2,ans);
    }
    debug(ans);

    if (ans >= 100000000) {
        cout << -1 << endl;
    } else{
        cout << ans << endl;
    }
    return 0;
}
