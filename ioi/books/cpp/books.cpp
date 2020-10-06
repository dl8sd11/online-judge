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
template<typename T> ostream &operator << (ostream &os, const pair<T,T> &v) {
    return os << "{" << v.X << "," <<v.Y << "}";
}
template<typename T> ostream &operator << (ostream &os, const vector<T> &v) {
    return __printRng(os, ALL(v));
}
template<typename T> ostream &operator << (ostream &os, const deque<T> &v) {
    return __printRng(os, ALL(v));
}
template<typename T> ostream &operator << (ostream &os, const set<T> &v) {
    return __printRng(os, ALL(v));
}
#define IOS()
#else
#define debug(...)
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#endif
#include "books.h"


int n, mn, mx;
ll sum;
vector<int> vis, p;

void dfs (int nd) {
    mn = min(nd, mn);
    mx = max(nd, mx);
    vis[nd] = true;
    sum += abs(nd-p[nd]);
    if (!vis[p[nd]]) {
        dfs(p[nd]);
    }
}

ll minimum_walk(std::vector<int> P, int s) {
    p = P;
    n = SZ(p);
    vis.clear();
    vis.resize(n, 0);
    sum = 0;

    vector<pii> rng;
    for (int i=0; i<n; i++) {
        if (!vis[i] && p[i] != i) {
            mn = i;
            mx = i;
            dfs(i);
            rng.eb(mn, mx);
        }
    }

    sort(ALL(rng));
    vector<pii> nrng;

    int lst = -1;
    int L = -1;
    for (pii r : rng) {
        if (r.X > lst) {
            if (L != -1) {
                nrng.eb(L, lst);
            }
            L = r.X;
            lst = r.Y;
        } else {
            lst = max(lst, r.Y);
        }
    }
    if (L==-1) return 0;
    nrng.eb(L, lst);

    debug(nrng);
    debug(sum);



    for (int i=1; i<SZ(nrng); i++) {
        sum += 2 * (nrng[i].X - nrng[i-1].Y);
    }
    if (s <= nrng[0].X) {
        sum += 2 * (nrng[0].X - s);
    } else if (s >= nrng.back().Y) {
        sum += 2 * (s - nrng.back().Y);
    } else {
        pii bg;
        for (auto v : nrng) {
            if (v.Y >= s) {
                bg = v;
                break;
            }
        }
        
        if (bg.X < s) {
            int sz = bg.Y - bg.X + 1;
            set<int> alive;
            deque<int> bfs;
            set<int> vs;
            vector<int> dis(n, 0x3f3f3f3f);
            for (int i=bg.X; i<=bg.Y; i++) {
                alive.insert(i);
            }
            alive.erase(s);
            bfs.emplace_back(s);

            dis[s] = 0;
            while (bfs.size()) {
                debug(bfs);
                int nd = bfs.front();
                bfs.pop_front();
                if (vs.count(nd)) continue;
                vs.insert(nd);

                int l = nd, r = p[nd];
                if (l > r) swap(l, r);

                while (l < r) {
                    auto ptr = alive.lower_bound(l);
                    if (ptr == alive.end() || *ptr > r) {
                        break;
                    }
                    bfs.emplace_front(*ptr);
                    dis[*ptr] = min(dis[*ptr], dis[nd]);
                    l = *ptr;
                    alive.erase(ptr);
                }

                if (alive.count(nd+1)) {
                    dis[nd+1] = min(dis[nd+1], dis[nd] + 1);
                    bfs.emplace_back(nd + 1);
                }
                if (alive.count(nd-1)) {
                    dis[nd-1] = min(dis[nd-1], dis[nd] + 1);
                    bfs.emplace_back(nd - 1);
                }
            }

            sum += min(dis[bg.X], dis[bg.Y]) * 2;
            debug(dis);
        }
    }

	return sum;
}
