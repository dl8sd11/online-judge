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

int n, s[MAXN], m;

struct node {
    int l, r;
    node *lc, *rc;
    int data;
};
node *seg[MAXN];

node *build (int l, int r) {
    if (l == r - 1) {
        return new node{l, r, nullptr, nullptr, 0};
    }
    int mid = (l + r) >> 1;
    return new node{l, r, build(l, mid), build(mid, r), 0};
}

node *add (int x, int v, node *nd) {
    node *ret = new node(*nd);
    if (x == nd->l && x == nd->r - 1) {
        ret->data += v;
    } else {
        int mid = (nd->l + nd->r) >> 1;
        if (x >= mid) {
            ret->rc = add(x, v, nd->rc);
        } else {
            ret->lc = add(x, v, nd->lc);
        }
        ret->data = ret->lc->data + ret->rc->data;
    }
    return ret;
}

int qry (int l, int r, node *nd) {
    if (l == nd->l && r == nd->r) {
        return nd->data;
    } else {
        int mid= nd->l + nd->r >> 1;
        if (l >= mid) {
            return qry(l, r, nd->rc);
        } else if (r <= mid) {
            return qry(l, r, nd->lc);
        } else {
            return qry(l,mid,nd->lc) + qry(mid,r,nd->rc);
        }
    }
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    seg[0] = build(1, n+1);
    REP1 (i, n) {
        cin >> s[i];
    }
    REP1 (i, n) {
        seg[i] = add(s[i], 1, seg[i-1]);
    }

    while (m--) {
        int l, r, a, b;
        cin >> l >> r >> a >> b;
        b++;
        cout << qry(a, b, seg[r]) - qry(a, b, seg[l-1]) << endl;
    }

}
