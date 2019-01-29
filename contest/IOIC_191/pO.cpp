#include <bits/stdc++.h>
using namespace std;

struct treap {
    long long pos, val, sum;
    int sz, pri;
    treap *lc, *rc;
    treap(long long p, long long v): 
          pos(p), sum(v), val(v), sz(1), pri(rand()), lc(nullptr), rc(nullptr) {}
    void pull() {
        sum = val, sz = 1;
        if (lc) sz += lc->sz, sum += lc->sum;
        if (rc) sz += rc->sz, sum += rc->sum;
    }
};

treap *merge(treap *a, treap *b) {
    if (!a || !b) return a ? a : b;
    if (a->pri > b->pri) return a->rc = merge(a->rc, b), a->pull(), a;
    else return b->lc = merge(a, b->lc), b->pull(), b;
}

void split(treap *t, long long k, treap *&a, treap *&b) {
    if (!t) return a = b = nullptr, void();
    if (t->pos <= k) a = t, split(t->rc, k, a->rc, b), a->pull();
    else b = t, split(t->lc, k, a, b->lc), b->pull();
}

map<long long, int> dx, dy;

int rev(long long x, map<long long, int> &d) {
    if (d.find(x) != d.end()) return d[x];
    int res = (int)d.size();
    return d[x] = res;
}

const int maxn = 1e6 + 5;
treap *tx[maxn], *ty[maxn];

void insert(treap *&t, long long p, long long v) {
    treap *a, *b;
    split(t, p - 1, a, b);
    t = merge(merge(a, new treap(p, v)), b);
}

long long query(treap *t, long long p) {
    treap *a, *b;
    split(t, p, a, b);
    long long res = (a ? a->sum : 0);
    t = merge(a, b);
    return res;
}

int main() {
    int n; scanf("%d", &n);
    long long last = 0;
    for (int i = 0; i < maxn; ++i) {
        tx[i] = nullptr;
        ty[i] = nullptr;
    }
    for (int i = 0; i < n; ++i) {
        int t; scanf("%d", &t);
        if (t == 1) {
            long long xa, ya, xb, yb, w; 
            scanf("%lld%lld%lld%lld%lld", &xa, &ya, &xb, &yb, &w); 
            assert(xa == xb || ya == yb);
            if (xa == xb) {
                long long p = rev(xa, dx);
                insert(tx[p], min(ya, yb) + 0, +w);
                insert(tx[p], max(ya, yb) + 1, -w);
            } else {
                long long p = rev(ya, dy);
                insert(ty[p], min(xa, xb) + 0, +w);
                insert(ty[p], max(xa, xb) + 1, -w);
            }
        } else {
            long long x, y; scanf("%lld%lld", &x, &y);
            last = query(tx[rev(x, dx)], y) + query(ty[rev(y, dy)], x);
            printf("%lld\n", last);
        }
    }
    return 0;
}