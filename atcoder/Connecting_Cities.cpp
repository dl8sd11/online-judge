#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int MAXN = 200003;
const ll INF = 1e17;

ll n,d,a[MAXN];
struct node {
    ll l,r;
    node *lc,*rc;
    ll data,tag,fr,mn;
    ll get() {
        return data+tag;
    }
    void pull() {
        if (lc) {
            data = min(lc->get(),rc->get());
            if (data < mn) {
                mn = data;
            }
            if (lc->mn < rc->mn) {
                fr = lc->fr;
            } else {
                fr = rc->fr;
            }
        }
    }
    void push() {
        data += tag;
        if (lc) {
            lc->tag += tag;
            rc->tag += tag;
        }
        mn = min(data,mn);
        tag = 0;
    }
};

node *root;
node *build(ll l,ll r) {
    if (r == l + 1) {
        return new node{l,r,0,0,a[l]+d*l,0,l,a[l]+d*l};
    }
    ll mid = (l + r) >> 1;
    node *ret = new node{l,r,build(l,mid),build(mid,r),0,0,0,INF};
    ret->pull();
    return ret;
}

void add(ll l,ll r,ll val,node *nd=root) {
    if (l == nd->l && r == nd->r) {
        nd->tag += val;
        return;
    }
    nd->push();
    ll mid = (nd->l + nd->r) >> 1;
    if (l >= mid) {
        add(l,r,val,nd->rc);
    } else if (r <= mid) {
        add(l,r,val,nd->lc);
    } else {
        add(l,mid,val,nd->lc);
        add(mid,r,val,nd->rc);
    }
    nd->pull();
}

pair<ll,ll> query(ll l,ll r,node *nd=root) {
    nd->push();
    if (l == nd->l && r == nd->r) {
        return {nd->mn,nd->fr};
    }
    ll mid = (nd->l + nd->r) >> 1;
    if (l >= mid) {
        return query(l,r,nd->rc);
    } else if (r <= mid) {
        return query(l,r,nd->lc);
    } else {
        pair<ll,ll> lret,rret;
        lret = query(l,mid,nd->lc);
        rret = query(mid,r,nd->rc);
        if (lret.first < rret.first) {
            return lret;
        } else {
            return rret;
        }
    }
}

void vis(ll pos,node *nd=root) {
    if (nd->l == pos && nd->r == pos+1) {
        nd->data = INF;
        nd->mn = INF;
        nd->tag = 0;
        return;
    }
    ll mid = (nd->l + nd->r) >> 1;
    nd->push();
    if (pos >= mid) {
        vis(pos,nd->rc);
    } else {
        vis(pos,nd->lc);
    }
    nd->pull();
}
int main () {
    cin >> n >> d;
    for (ll i=0;i<n;i++) {
        cin >> a[i];
    }
    root = build(0,n);

    ll ans = 0,cur = 0;
    vis(0);

    for (ll i=0;i<n-1;i++) {
        pair<ll,ll> bst = query(0,n);
        cout << bst.first << " " << bst.second << endl;
        ans += bst.first + a[cur];
        vis(bst.second);
        if (bst.second > cur) {
            add(cur+1,n,-d*(bst.second-cur));
            add(0,bst.second,d*(bst.second-cur));
        } else {
            add(0,bst.second+1,-d*(cur-bst.second));
            add(bst.second+1,n,d*(cur-bst.second));
        }
        cur = bst.second;
    }

    cout << ans << endl;
}