#include <bits/stdc++.h>
using namespace std;

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
template<typename _a,typename _b> ostream &operator << (ostream &_s,map<_a,_b> &_c){return _OUTC(_s,ALL(_c));}
template<typename _t> void pary(_t _a,_t _b){_OUTC(cerr,_a,_b);cerr<<endl;}
#define IOS()
#else
#define debug(...)
#define pary(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#endif


const int maxn = 1e5 + 10, inf = 1e9 + 1;
vector<int> G[maxn], vtx;
int dep[maxn], fa[maxn], sz[maxn], mx[maxn], p[maxn], dis[20][maxn], ans[maxn];
bool v[maxn];

void get_center(int now) {
    v[now] = true; vtx.push_back(now);
    sz[now] = 1; mx[now] = 0;
    for (int u : G[now]) if (!v[u]) {
        get_center(u);
        mx[now] = max(mx[now], sz[u]);
        sz[now] += sz[u];
    }
}

void get_dis(int now, int d, int cnt) {
  debug(now,d,cnt);
    dis[d][now] = cnt;
    v[now] = true;
    for (int u : G[now]) if (!v[u]) {
        get_dis(u, d, cnt + 1);
    }
}

int dfs(int now, int fa, int d) {
    get_center(now);
    int c = -1;
    for (int i : vtx) {
        if (max(mx[i], (int)vtx.size() - sz[i]) <= (int)vtx.size() / 2) c = i;
        v[i] = false;
    }
    debug(c);
    get_dis(c, d, 0);
    for (int i : vtx) v[i] = false;
    v[c] = true; vtx.clear();
    dep[c] = d; p[c] = fa;
    for (int u : G[c]) if (u != fa && !v[u]) {
        dfs(u, c, d + 1);
    }
    return c;
}

void modify(int now) {
    ans[now] = 0;
    int cur = now;
    for (int d = dep[now]; d >= 0; --d) {
        ans[cur] = min(ans[cur], ans[now] + dis[d][now]);
        cur = p[cur];
    }
}

int query(int now) {
    int ret = inf;
    int cur = now;
    for (int d = dep[now]; d >= 0; --d) {
        ret = min(ret, ans[cur] + dis[d][now]);
        cur = p[cur];
    }
    return ret;
}

int main() {
    ios_base::sync_with_stdio(false); cin.tie(0);
    int n, m; cin >> n >> m;
    for (int i = 0; i < n - 1; ++i) {
        int a, b; cin >> a >> b;
        G[a].push_back(b); G[b].push_back(a);
    }
    int c = dfs(1, 0, 0);
    fill(ans, ans + maxn, inf);
    modify(1);
    while (m--) {
        int t, vi; cin >> t >> vi;
        if (t == 1) modify(vi);
        else cout << query(vi) << endl;
    }
    return 0;
}
