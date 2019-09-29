#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#define ALL(i) i.begin(), i.end()
#ifdef tmd
#define IOS()
#define TIME(i) Timer i(#i)
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
class Timer {
private:
    string scope_name;
    chrono::high_resolution_clock::time_point start_time;
public:
    Timer (string name) : scope_name(name) {
        start_time = chrono::high_resolution_clock::now();
    }
    ~Timer () {
        auto stop_time = chrono::high_resolution_clock::now();
        auto length = chrono::duration_cast<chrono::microseconds>(stop_time - start_time).count();
        double mlength = double(length) * 0.001;
        debug(scope_name, mlength);
    }
};
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define TIME(i)
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 1000006;
const ll MOD = 1000000007;

vector<int> node[MAXN];
void mrg(vector<int> &x, vector<int> &y) {
    auto it = x.size();
    x.insert(x.end(), y.begin(), y.end());
    inplace_merge(x.begin(), x.begin()+it, x.end());
    y.clear();
}

int n, a[MAXN], p[MAXN], cnt[MAXN];
vector<int> edge[MAXN];

const int L = 1;

void build (int nd) {
    node[nd].emplace_back(a[nd]);
    for (auto v : edge[nd]) {
        build(v);
    }
    for (auto v : edge[nd]) {
        mrg(node[nd], node[v]);
    }
}

void arrg (int nd) {
    sort(edge[nd].begin(), edge[nd].end(), [](int x, int y) {
        ll l = 0, r = 0;
        if (SZ(node[x]) > SZ(node[y])) {
            for (auto e : node[x]) {
                l += lower_bound(node[y].begin(), node[y].end(), e) - node[y].begin();
                r += node[y].end() - upper_bound(node[y].begin(), node[y].end(), e);
            }
        } else {
            for (auto e : node[y])  {
                l += node[x].end() - upper_bound(node[x].begin(), node[x].end(), e);
                r += lower_bound(node[x].begin(), node[x].end(), e) - node[x].begin();
            }
        }
        return l < r;
    });
}
#ifdef tmd
vector<int> ord;
bool vis[MAXN];
void pre_dfs (int nd) {
    vis[nd] = true;
    ord.emplace_back(a[nd]);
    for (auto v : edge[nd]) {
        if (!vis[v]) {
            pre_dfs(v);
        }
    }
}

namespace BIT {
    ll bit[MAXN];
    void add (int pos, ll val) {
        pos++;
        for (;pos<MAXN;pos+=-pos&pos) {
            bit[pos] += val;
        }
    }

    ll qry (int pos) {
        ll ret = 0;
        pos++;
        for (;pos>0;pos-=-pos&pos) {
            ret += bit[pos];
        }
        return ret;
    }
}
ll eval () {
    ll ret = 0;
    for (auto v : ord) {
        ret += BIT::qry(MAXN-2) - BIT::qry(v);
        BIT::add(v, 1);
    }
    return ret;
}
#endif

inline int redi() {
    int ret = 0,f = 0;char ch = getchar_unlocked();
    while (!isdigit (ch)) {
        if (ch == '-') f = 1;
        ch = getchar_unlocked();
    }
    while (isdigit (ch)) {
        ret = ret*10  + ch - 48;
        ch = getchar_unlocked();
    }
    return f?-ret:ret;
}
inline void print(int x) {
    if(x<0) {putchar_unlocked('-');x=-x;}
    int y=10,len=1;
    while(y<=x)    {y*=10;len++;}
    while(len--){y/=10;putchar_unlocked(x/y+48);x%=y;}
}
/*********************GoodLuck***********************/
int main () {
    // IOS();
{TIME(mai);
    n = redi();
    {
        TIME(ipt);
        REP1 (i, n) {
            a[i] = redi();
        }

        for (int j=2; j<=n; j++) {
            p[j] = redi();
            cnt[p[j]]++;
        }

        for (int j=2; j<=n; j++) {
            if (edge[p[j]].empty()) {
                edge[p[j]].resize(cnt[p[j]]);
                cnt[p[j]] = 0;
            }
            edge[p[j]][cnt[p[j]]++] = j;
        }
    }
    build(1);

    REP1 (i, n) {
        if (edge[i].empty()) {
            putchar_unlocked('0');
            putchar_unlocked('\n');
        } else {
            REP (j, SZ(edge[i])) {
                print(edge[i][j]);
                putchar_unlocked(" \n"[j==SZ(edge[i])-1]);
            }
        }
    }}
#ifdef tmd
    pre_dfs(1);
    cout << "Algo: " << eval() << endl;
#endif
    return 0;
}
