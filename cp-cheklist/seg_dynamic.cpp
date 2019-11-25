#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
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

struct Segment {
    struct node {
        int l, r;
        node *lc, *rc;
        int data;
        void pull () {
            if (lc) {
                data = max(data, lc->data);
            }
            if (rc) {
                data = max(data, rc->data);
            }
        }
    };
    node *root;
    Segment () {
        root = new node{0,MAXN, nullptr, nullptr, 0};
    }
    void chg (int x, int val, node *nd) {
        debug(nd->l, nd->r);
        if (x == nd->l && x == nd->r - 1) {
            nd->data = max(nd->data, val);
        } else {
            int mid = (nd->l + nd->r) >> 1;
            if (x >= mid) {
                if (!nd->rc) {
                    nd->rc = new node{mid, nd->r,nullptr, nullptr, 0};
                }
                chg(x, val, nd->rc);
            } else {
                if (!nd->lc) {
                    nd->lc = new node{nd->l, mid,nullptr, nullptr, 0};
                }
                chg(x, val, nd->lc);
            }
            nd->pull();
        }
    }

    int qry (int l, int r, node *nd) {
        debug(l, r);
        if (!nd) {
            return 0;
        } else if (l == nd->l && r == nd->r) {
            return nd->data;
        } else {
            int mid = (nd->l + nd->r) >> 1;
            if (l >= mid) {
                return qry(l, r, nd->rc);
            } else if (r <= mid) {
                return qry(l, r, nd->lc);
            } else {
                return max(qry(l, mid, nd->lc), qry(mid, r, nd->rc));
            }
        }
    }
} seg[MAXN];

int n, m;
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> m;

    int ans = 0;
    while (m--) {
        int u, v, w;
        cin >> u >> v >> w;
        int mx = seg[u].qry(0, w, seg[u].root);
        seg[v].chg(w, mx+1, seg[v].root);
        debug(mx, u, v);
        ans = max(ans, mx+1);
    }

    cout << ans << endl;
}
