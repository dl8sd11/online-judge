#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;

struct node {
    node *lc, *rc;
    int key, pri, sz;
    bool rev;

    void pull () {
        sz = 1;
        if (lc) {
            sz += lc->sz;
        }
        if (rc) {
            sz += rc->sz;
        }
    }

    void push () {
        if (rev) {
            if (lc) {
                lc->rev ^= 1;
            }
            if (rc) {
                rc->rev ^= 1;
            }
            swap(lc, rc);
            rev = 0;
        }
    }
};

node* mrg (node *a, node *b) {
    if (!a || !b) {
        return a ? a : b;
    } else {
        if (a->pri > b->pri) {
            a->push();
            a->rc = mrg(a->rc, b);
            a->pull();
            return a;
        } else {
            b->push();
            b->lc = mrg(a, b->lc);
            b->pull();
            return b;
        }
    }
}

int SIZ (node *nd) {
    return nd ? nd->sz : 0;
}

void split (node *o, node *&a, node *&b, int k) {
    if (!o) {
        a = b = 0;
        return;
    } else {
        o->push();
        if (SIZ(o->lc)+1 <= k) {
            a = o;
//            a->push();
            split(a->rc, a->rc, b, k-(SIZ(a->lc)+1));
            a->pull();
        } else {
            b = o;
//            b->push();
            split(b->lc, a, b->lc, k);
            b->pull();
        }

    }
}

vector<int> ans;
void dfs (node *nd) {
    if (nd) {
        nd->push();
        dfs(nd->lc);
        ans.eb(nd->key);
        dfs(nd->rc);
    }
}

void pt (node *nd) {
    if (nd) {
        nd->push();
        pt(nd->lc);
        cout << nd->key << " ";
        pt(nd->rc);
    }
}

int n, m;
node *root;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;

    REP1 (i, n) {
        if (root) {
            root = mrg(root, new node{0,0,i,rand(),1,0});
        } else {
            root = new node{0,0,i,rand(),1,0};
        }
    }

    while (m--) {
        int l, r;

        #ifdef tmd
        l = rand() % n + 1;
        r = rand() % n + 1;
        if (l > r) {
            swap(l, r);
        }

        debug(l, r);

        #else
        cin >> l >> r;
        #endif // tmd
        node *L, *M, *R;
        split(root, L, M, l-1);
        debug(SIZ(L), SIZ(M));
        split(M, M, R, r-l+1);

        debug(SIZ(L), SIZ(M), SIZ(R));
        assert(SIZ(L) == l - 1);
        assert(SIZ(M) == r-l+1);
        assert(SIZ(R) == n-r);

        M->rev ^= 1;
        root = mrg(L, mrg(M, R));
        assert(SIZ(root) == n);

//        pt(root);
//        cout << endl;

    }

    dfs(root);

    for (int i=0; i<n; i++) {
        cout << ans[i] << " \n"[i==n-1];
    }
}
