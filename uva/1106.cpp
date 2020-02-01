#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 lll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;

typedef complex<lll> point;

lll dot (const point &p1, const point &p2) {
    return (conj(p1)*p2).real();
}

lll f (const point &p, lll x) {
    return dot(p, {x, 1});
}

struct LiChaoTree {
    struct Node {
        int l, r;
        Node *lc, *rc;
        point pt;
    };
    Node *root;

    LiChaoTree () {
        root = new Node{0, MOD, nullptr, nullptr, {0, 0}};
    }

    void add_line (point pt, Node *nd) {
        int mid = (nd->l + nd->r) >> 1;
        bool l = f(nd->pt, nd->l) < f(pt, nd->l);
        bool m = f(nd->pt, mid) < f(pt, mid);
        if (m) {
            swap(pt, nd->pt);
        }
        if (nd->l == nd->r - 1) {
            return;
        } else {
            if (l != m) {
                if (!nd->lc) {
                    nd->lc = new Node{nd->l, mid, nullptr, nullptr, {0, 0}};
                }
                add_line(pt, nd->lc);
            } else {
                if (!nd->rc) {
                    nd->rc = new Node{mid, nd->r, nullptr, nullptr, {0, 0}};
                }
            }
        }
    }

    lll qry (lll x, Node *nd) {
        if (!nd) {
            return 0;
        } else {
            int mid = (nd->l + nd->r) >> 1;
            if (x >= mid) {
                return max(qry(x, nd->rc), f(nd->pt, x));
            } else {
                return max(qry(x, nd->lc), f(nd->pt, x));
            }
        }
    }

    void del (Node *nd) {
        if (nd->lc) {
            del(nd->lc);
        }
        if (nd->rc) {
            del(nd->rc);
        }
        delete nd;
    }
};

int n, c, D, macnt;
lll dp[MAXN];

struct Mac {
    int d, p, r, g;
    bool operator < (const Mac &cp) const {
        return d < cp.d;
    }
} mac[MAXN];

/*********************GoodLuck***********************/

int main () {
    IOS();
    int tc = 0;
    while (cin >> n >> c >> D && n && c && D) {
        tc++;
        macnt = 0;
        LiChaoTree cht;
        mac[macnt++] = {0, 0, c, 0};
        mac[macnt++] = {D, 0, 0, 0};
        REP (i, n) {
            int d ,p ,r ,g;
            cin >> d >> p >> r >> g;
            mac[macnt++] = {d, p , r ,g};
        }

        sort(mac, mac+macnt);
        for (int i=0; i<macnt; ) {
            int hd = i;
            while (i<macnt && mac[i].d == mac[hd].d) {
                dp[i] = cht.qry(mac[i].d, cht.root);
                i++;
            }
            for (int j=hd; j<i; j++) {
                if (dp[j] >= mac[j].p) {
                    lll a = mac[j].g, b = dp[j]-mac[j].g-1LL*j*mac[j].g+mac[j].r-mac[j].p;
                    cht.add_line({a, b}, cht.root);
                }
            }
        }

        cht.del(cht.root);
        cout << "Case " << tc << ": " << ll(dp[macnt-1]) << endl;
    }
}
/*
6 10 20
6 12 1 3
1 9 1 2
3 2 1 2
8 20 5 4
4 11 7 4
2 10 9 1
0 0 0
*/
