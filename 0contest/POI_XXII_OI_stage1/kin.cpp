#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define REP(i,n) for(ll i=0;i<n;i++)
#define REP1(i,n) for(ll i=1;i<=n;i++)
#define SZ(i) ll(i.size())
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
#ifdef tmd
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#endif
const ll INF = 0x3f3f3f3f3f3f3f3f;
const ll MAXN = 1000003;

namespace SEG {
    struct node {
        int l,r;
        node *lc,*rc;
        ll data,tag;
        void push() {
            data += tag;
            if (lc && rc) {
                lc->tag += tag;
                rc->tag += tag;
            }
            tag = 0;
        }

        ll get() {
            return data + tag;
        }

        void pull() {
            if (lc && rc) {
                data = max(lc->get(),rc->get());
            }
        }
    };
    node *root;
    node *build(int l,int r) {
        if (r == l + 1) {
            return new node{l,r,0,0,0,0};
        }
        int mid = (l + r) >> 1;
        return new node{l,r,build(l,mid),build(mid,r),0,0};
    }

    ll query(int l,int r,node *nd) {
        if (l >= r) {
            return 0;
        }
        if (l == nd->l && r == nd->r) {
            return nd->get();
        }
        nd->push();
        int mid = (nd->l + nd->r) >> 1;
        if (l >= mid) {
            return query(l,r,nd->rc);
        } else if (r <= mid) {
            return query(l,r,nd->lc);
        } else {
            return max(query(l,mid,nd->lc),query(mid,r,nd->rc));
        }
    }

    void add(int l,int r,node *nd,ll val) {
        if (l >= r) {
            return;
        }
        if (nd->l == l && nd->r == r) {
            nd->tag += val;
            return;
        }
        nd->push();
        int mid = (nd->l + nd->r) >> 1;
        if (l >= mid) {
            add(l,r,nd->rc,val);            
        } else if (r <= mid) {
            add(l,r,nd->lc,val);
        } else {
            add(l,mid,nd->lc,val);
            add(mid,r,nd->rc,val);
        }
        nd->pull();
    }
};
int n,m,f[MAXN];
ll w[MAXN];
pii lst[MAXN];
int main () {
    IOS();
    cin >> n >> m;
    SEG::root = SEG::build(0,n);
    REP (i,n) {
        cin >> f[i];
    }
    REP1 (i,m) {
        cin >> w[i];
        lst[i].X = -1;
        lst[i].Y = -2;
    }

    ll ans = 0;

    REP (i,n) {
        if (lst[f[i]].Y != -2) {
            SEG::add(lst[f[i]].Y+1,lst[f[i]].X+1,SEG::root,-w[f[i]]);
        }
        swap(lst[f[i]].X,lst[f[i]].Y);
        lst[f[i]].X = i;
        SEG::add(lst[f[i]].Y+1,lst[f[i]].X+1,SEG::root,w[f[i]]);
        ans = max(ans,SEG::query(0,i+1,SEG::root));
    }
    cout << ans << endl;
}
