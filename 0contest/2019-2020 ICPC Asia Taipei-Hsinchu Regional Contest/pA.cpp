#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 21;
const ll MOD = 1000000007;

typedef array<pii,11> ap;

pii win = {2, 4};

int len[MAXN];
bool dir[MAXN];
ap init;

const int W = 6;
int bd[MAXN][MAXN];

set<ap> seen;

struct State {
    ap poss;
    int step;
};

int dx[] = {0, 1};
int dy[] = {1, 0};

bool vis[MAXN][MAXN];

void build(const ap &cur) {
    memset(vis, 0, sizeof(vis));

    REP1 (i, 10) {
        int x, y;
        tie(x, y) = cur[i];
        REP (j, len[i]) {
            vis[x][y] = true;

            x += dx[dir[i]];
            y += dy[dir[i]];
        }
    }
}

inline bool valid (int x, int y) {
    return x >= 0 && x < 6 && y >= 0 && y < 6;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    REP (i, W) {
        REP (j, W) {
            cin >> bd[i][j];
        }
    }

    REP1 (id, 10) {
        pii hd = {-1, -1};
        REP (i, W) {
            REP (j, W) {
                if (bd[i][j] == id) {
                    hd = {i, j};
                    break;
                }
            }
            if (hd.X != -1) {
                break;
            }
        }

        if (hd.X != -1) {
            if (bd[hd.X][hd.Y + 1] == id) {
                dir[id] = 0;
                len[id] = bd[hd.X][hd.Y+2] == id ? 3 : 2;
            } else {
                dir[id] = 1;
                len[id] = bd[hd.X+2][hd.Y] == id ? 3 : 2;
            }
        }

        init[id] = hd;
    }

    if (init[1] == win) {
        cout << 2 << endl;
        return 0;
    }

    State istate = {init, 0};
    queue<State> que;
    que.emplace(istate);
    seen.insert(init);

    while (que.size()) {
        State cur = que.front();
        que.pop();

        build(cur.poss);
        REP1 (i, 10) {
            if (len[i] > 0) {
                for (int xx : {len[i], -1} ) {
                    int nx = cur.poss[i].X + dx[dir[i]] * xx;
                    int ny = cur.poss[i].Y + dy[dir[i]] * xx;

                    if (valid(nx, ny) && !vis[nx][ny]) {
                        ap nb = cur.poss;
                        nb[i].X += dx[dir[i]] * (xx > 0 ? 1 : -1);
                        nb[i].Y += dy[dir[i]] * (xx > 0 ? 1 : -1);

                        if (nb[1] == win) {
                            cout << cur.step + 3 << endl;
                            return 0;
                        }

                        if (!seen.count(nb) && cur.step + 1 <= 7) {
                            State nw = {nb, cur.step + 1};
                            seen.insert(nb);
                            que.emplace(nw);
                        }
                    }
                }
            }
        }
    }

    cout << -1 << endl;
}
