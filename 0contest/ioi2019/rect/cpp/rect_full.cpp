#include "rect.h"
#pragma GCC optimize("Ofast")
#pragma GCC target("avx,avx2,fma")
#pragma GCC optimize("unroll-loops")
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#ifdef tmd
#define debug(...) fprintf(stderr,"%d (%s) = ",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do (T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do (T &&x, S &&...y) {cerr<<x<<",";_do(y...);}
template<typename IT> ostream &printRng (IT bg, IT ed, ostream &os) {
    os<<"{";
    for (IT it=bg; it!=ed; it++) {
        if (it!=bg) {
            os<<",";
        }
        os<<(*it);
    }
    return os<<"}";
}
template<typename T> ostream &operator << (ostream &os, vector<T> &vec) {
    return printRng(vec.begin(), vec.end(), os);
}
template<typename T> ostream &operator << (ostream &os, pair<T,T> &vec) {
    return os<<"{"<<vec.first<<","<<vec.second<<"}";
}
template<typename T> void pary (T bg, T ed) {
    printRng(bg,ed,cerr);
    cerr<<endl;
}
#else
#define debug(...)
#define pary(...)
#endif // tmd

const int MAXN = 2502;
int szh, szg, n, m;
pii h[MAXN], g[MAXN];
short dw[4][MAXN][MAXN], ri[4][MAXN][MAXN];

int bit[MAXN];

void add (int x, int y) {
    for (x++;x<MAXN;x+=-x&x) {
        bit[x] += y;
    }
}

int sqry (int x) {
    int ret = 0;
    for (x++;x>0; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

int solve () {
    vector<pair<int,int> > qry;
    for (int i=0; i<szg; i++) {
        qry.emplace_back(g[i], i+1);
    }
    sort(qry.begin(), qry.end());
    memset(bit, 0, sizeof(bit));

//    debug(qry);
    int res = 0, sum = 0;
    for (int i=szh-1; i>=0; i--) {
        res += h[i];

        add(h[i], 1);
        sum++;

        while (qry.size() && qry.back().first>=i) {
            res -= sum - sqry(qry.back().second-1);
            debug(sqry(qry.back().second-1));
            qry.pop_back();
        }

    }

    if (res) {
        pary(h, h+szh);
        pary(g, g+szg);
        debug(res)
    }

    return res;
}

vector<vector<int> > G;
void build () {
    int mx[MAXN] = {};

    for (int l=0; l<m; l++) {
        memset(mx, 0, sizeof(mx));
        for (int r=l+2; r<m; r++) {
            for (int i=0; i<n; i++) {
                mx[i] = max(mx[i], G[i][r-1]);
            }
            int lst = n;
            for (int i=n-1; i>=0; i--) {
                dw[i][l][r-1] = lst - i - 1;
                if (mx[i] >= min(G[i][l], G[i][r])) {
                    lst = i;
                }
            }
        }
    }

    for (int u=0; u<n; u++) {
        memset(mx, 0, sizeof(mx));
        for (int d=u+2; d<n; d++) {
            for (int i=0; i<m; i++) {
                mx[i] = max(mx[i], G[d-1][i]);
            }
            int lst = m;
            for (int i=m-1; i>=0; i--) {
                ri[u][i][d-1] = lst - i - 1;
                if (mx[i] >= min(G[u][i], G[d][i])) {
                    lst = i;
                }
            }
        }
    }
}

vector<vector<int> > flip (vector<vector<int> > vec) {
    vector<vector<int> > res;
    for (int j=0; j<vec[0].size(); j++) {
        vector<int> cur;
        for (int i=0; i<vec.size(); i++) {
            cur.emplace_back(vec[i][j]);
        }
        res.emplace_back(cur);
    }
    return res;
}

long long count_rectangles(std::vector<std::vector<int> > a) {
    G = a;
	n = a.size();
	m = a[0].size();
	build();
    ll res = 0;
    for (int i=0; i<n; i++) {
        for (int j=0; j<m; j++) {
            szh = 0, szg = 0;
            for (int k=j+1; k<m; k++) {
                h[szh++] = dw[i][j][k];
            }
            for (int k=i+1; k<n; k++) {
                g[szg++] = ri[i][j][k];
            }

            debug(i, j);
            res += solve();
        }
    }
    return res;
}
