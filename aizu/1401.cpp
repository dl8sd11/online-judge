#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
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

const int MAXN = 51;
const ll MOD = 1000000007;

int w, d, n;
int ans[MAXN][MAXN];

typedef pair<int,int> pii;
struct BFS {
    const int shift = 200;
    vector<pii> data[405];

    void add (int hei, pii cell) {
        data[hei+shift].emplace_back(cell);
    }

    vector<pii> get(int hei) {
        return data[hei+shift];
    }
} bfs;

struct Walker {
    const int sz = 4;
    int dx[4] = {-1, 0, 1, 0};
    int dy[4] = {0, -1, 0, 1};

    bool validPosition (pii cur) {
        return cur.first >= 1 && cur.first <= w && cur.second >= 1 && cur.second <= d;
    }

    vector<pii> validMoves (pii cur) {
        vector<pii> ret;
        for (int i=0; i<sz; i++) {
            pii nw = {cur.first+dx[i], cur.second+dy[i]};
            if (validPosition(nw)) {
                ret.emplace_back(nw);
            }
        }
        return ret;
    }
} walker;

const int INF = 0x3f3f3f3f;
/*********************GoodLuck***********************/
int main () {
    IOS();

    memset(ans, INF, sizeof(ans));

    cin >> w >> d >> n;
    REP (i, n) {
        int hei;
        pii cell;
        cin >> cell.first >> cell.second >> hei;
        bfs.add(hei, cell);
        ans[cell.first][cell.second] = hei;
    }

    for (int i=200; i>= -200; i--) {
        vector<pii> lst = bfs.get(i);
        for (auto cur : lst) {

            vector<pii> valid = walker.validMoves(cur);
            for (auto nw : valid) {
                if (ans[nw.first][nw.second] == INF) {
                    bfs.add(i-1, nw);
                    ans[nw.first][nw.second] = i-1;
                }
            }
        }
    }
#ifdef tmd
    for (int i=1; i<=w; i++) {
        for (int j=1; j<=d; j++) {
                cout << ans[i][j] << " \n"[j==d];
        }
    }
#endif // tmd

    int sum = 0;
    bool bad = false;
    for (int i=1; i<=w; i++) {
        for (int j=1; j<=d; j++) {
            if (i>1 && abs(ans[i][j]-ans[i-1][j])>1) {
                bad = true;
            }
            if (j>1 && abs(ans[i][j]-ans[i][j-1])>1) {
                bad = true;
            }
            sum += ans[i][j];
        }
    }


    if (bad) {
        cout << "No" << endl;
    } else {
        cout << sum << endl;
    }
}
