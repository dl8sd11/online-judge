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

const int MAXN = 200005;
const ll MOD = 1000000007;

int n, q, k, a[MAXN];

struct Node {
    Node *lc, *rc;
    int mx, tag;

    void push () {
        if (!rc) {
            rc = new Node({0,0,0,0});
        }
        if (!lc) {
            lc = new Node({0,0,0,0});
        }
        lc->tag += tag;
        rc->tag += tag;

        mx += tag;
        tag = 0;
    }

    int get () {
        return mx + tag;
    }

    void pull () {
        mx = -MOD;
        if (lc) {
            mx = max(mx, lc->get());
        }
        if (rc) {
            mx = max(mx, rc->get());
        }
    }
};

Node *root;

void add (int l, int r, int val, Node *nd, int qL = 0, int qR = MOD) {
    l = max(l, qL);
    r = min(r, qR);
    if (l == qL && r == qR) {
        nd->tag += val;
    } else {
        int mid = (qL + qR) >> 1;

        nd->push();
        if (l >= mid) {
            add(l, r, val, nd->rc, mid, qR);
        } else if (r <= mid) {
            add(l, r, val, nd->lc, qL, mid);
        } else {
            add(l, mid, val, nd->lc, qL, mid);
            add(mid, r, val, nd->rc, mid, qR);
        }
        nd->pull();
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> q >> k;

    root = new Node({0,0,0,0});
    for (int i=0; i<n; i++) {
        cin >> a[i];
        add(a[i]-k, a[i]+1, 1, root);
    }

    cout << root->get() << endl;
    while (q--) {
        int x, y;
        cin >> x >> y;
        x--;

        add(a[x]-k, a[x]+1, -1, root);
        a[x] = y;
        add(a[x]-k, a[x]+1, 1, root);

        cout << root->get() << endl;
    }

}

