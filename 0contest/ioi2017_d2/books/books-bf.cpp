#include "books.h"
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define SZ(i) int(i.size())
#define ALL(i) i.begin(), i.end()
#define MEM(i,a) memset(i, (a), sizeof(i))
#define X first
#define Y second
#define eb emplace_back
#define pb push_back
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d-(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do (T &&x) {cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {cerr<<x<<", ";_do(y...);}
template<typename IT> ostream& __printRng (ostream &os, IT bg, IT ed) {
    for (IT it=bg; it!=ed; it++) {
        if (it!=bg) os << "," << *it;
        else os << "{" << *it;
    }
    return os << "}";
}
template<typename T> ostream &operator << (ostream &os, const vector<T> &v) {
    return __printRng(os, ALL(v));
}
template<typename T> ostream &operator << (ostream &os, const set<T> &v) {
    return __printRng(os, ALL(v));
}
#else
#define debug(...)
#endif


long long minimum_walk(std::vector<int> p, int s) {
    set<vector<int> > vis;
    queue<vector<int> > bfs;
    int n = SZ(p);
    vector<int> targ(n);
    iota(ALL(targ), 0);
    targ.eb(-1);
    targ.eb(s);

    int ans = 0;
    p.eb(-1);
    p.eb(s);
    bfs.emplace(p);
    vis.insert(p);
    swap(p[s], p[n]);
    vis.insert(p);
    bfs.emplace(p);
    while (bfs.size()) {
        int sz = bfs.size();
        for (int _i=0; _i<sz; _i++) {
            vector<int> cur = bfs.front();
            debug(cur, ans);
            bfs.pop();
            if (cur == targ) return ans;

            vector<int> mv = {cur[n+1]-1, cur[n+1]+1};
            for (int i : mv) {
                if (i < 0 || i >= n) continue;
                vector<int> nw = cur;
                nw[n+1] = i;
                if (vis.count(nw) == 0) {
                    vis.insert(nw);
                    bfs.emplace(nw);
                }
                swap(nw[i], nw[n]);
                if (vis.count(nw) == 0) {
                    vis.insert(nw);
                    bfs.emplace(nw);
                }
            }
        }
        ans++;
    }
	return -1;
}
