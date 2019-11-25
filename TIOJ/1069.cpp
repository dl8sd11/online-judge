#include <bits/stdc++.h>
#pragma GCC optimize("Ofast,unroll-loops,no-stack-protector")
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

const int MAXN = 1003;
const ll MOD = 1000000007;


int T, n, t[MAXN], x[MAXN], y[MAXN];
int to[MAXN*MAXN], nxt[MAXN*MAXN], head[MAXN], ecnt;

void add_edge (int f, int t) {
    to[ecnt] = t;
    nxt[ecnt] = head[f];
    head[f] = ecnt++;
}

int dist (int i, int j) {
    return abs(x[i] - x[j]) + abs(y[i] - y[j]);
}

int cnt, xp[MAXN], yp[MAXN];
bool vis[MAXN];

void init () {
    cnt = 0;
    memset(xp, -1, sizeof(xp));
    memset(yp, -1, sizeof(yp));
}

void greedy_matching () {
    REP (i, n) {
        for (int id=head[i]; id!=-1; id=nxt[id]) {
            int v = to[id];
            if (yp[v] == -1)  {
                cnt++;
                yp[v] = i;
                xp[i] = v;
                break;
            }
        }
    }
}

bool dfs (int nd) {
    for (int id=head[nd]; id!=-1; id=nxt[id]) {
        int v = to[id];
        if (!vis[v]) {
            vis[v] = true;
            if (yp[v] == -1 || dfs(yp[v])) {
                yp[v] = nd;
                xp[nd] = v;
                return true;
            }
        }
    }

    return false;
}

/*
1
6
0 1 1
5 4 3
5 3 4
1 5 6
4 5 8
4 7 7
*/
void dfs_matching () {
    REP (i, n) {
        if (xp[i] == -1) {
            memset(vis, 0, sizeof(vis));
            if (dfs(i)) {
                cnt++;
            }
        }
    }
}

inline char readchar()
{
    static const size_t bufsize = 65536;
    static char buf[bufsize];
    static char *p = buf, *end = buf;
    if (p == end) end = buf + fread_unlocked(buf, 1, bufsize, stdin), p = buf;
    return *p++;
}

template <class T> void input(T& a)
{
    static char p;
    while ((p = readchar()) < '0') ;
    a = p ^ '0';
    while ((p = readchar()) >= '0') a *= 10, a += p ^ '0';
}


/*********************GoodLuck***********************/
int main () {
    // IOS();
    input(T);

    REP (ts, T) {

        input(n);

        REP (i, n) {
            input(t[i]);
            input(x[i]);
            input(y[i]);
        }

        memset(head, -1, sizeof(head));
        ecnt = 0;
        REP (i, n) {
            REP (j, n) {
                if (i != j && dist(i, j) <= t[j] - t[i]) {
                    add_edge(i, j);
                }
            }
        }

        init();
        greedy_matching();
        dfs_matching();

        printf("%d\n", n-cnt);
    }
}
