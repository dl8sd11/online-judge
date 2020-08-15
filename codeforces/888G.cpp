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
template<typename T> ostream &operator << (ostream &os,const vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 200005;
const ll MOD = 1000000007;

struct Trie {
    struct Node {
        Node *ch[2];
        int sz;
    };
    Node *root;

    int SIZ (Node *nd) {
        return nd ? nd->sz : 0;
    }

    Trie () {
        root = new Node{{0,0}, 0};
    }

    void insert (int x) {
        Node *nd = root;
        for (int i=31; i>=0; i--) {
            int c = (x>>i) & 1;
            if (!nd->ch[c]) {
                nd->ch[c] = new Node{{0,0}, 0};
            }
            nd = nd->ch[c];
            nd->sz++;
        }
    }

    void erase (int x) {
        Node *nd = root;
        for (int i=31; i>=0; i--) {
            int c = (x>>i) & 1;
            nd = nd->ch[c];
            nd->sz--;
        }
    }

    int qry (int x) { // val
        Node *nd = root;
        int res = 0;
        for (int i=31; i>=0; i--) {
            int c = (x>>i) & 1;
            if (SIZ(nd->ch[c])) {
                res += c<<i;
                nd = nd->ch[c];
            } else {
                res += (!c)<<i;
                nd = nd->ch[!c];
            }
        }

        return res;
    }
} trie;

int n;

int djs[MAXN], sz[MAXN];
int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

bool mrg (int x, int y) {
    x = fnd(x), y = fnd(y);
    if (x == y) {
        return false;
    }
    if (sz[x] > sz[y]) {
        swap(x, y);
    }
    djs[x] = y;
    sz[y] += sz[x];
    return true;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n;

    vector<int> a(n);
    REP (i, n) {
#ifdef tmd
        a[i] = rand();
#else
        cin >> a[i];
#endif
    }
    sort(ALL(a));
    a.resize(unique(ALL(a))-a.begin());

    n = SZ(a);
    map<int,int> rev;
    REP (i, n) {
        djs[i] = i;
        sz[i] = 1;
        rev[a[i]] = i;
        trie.insert(a[i]);
    }

    ll ans = 0;
    int itr = 0;
    while (true) {
        map<int,vector<int> > gps;
        int tmp = 0;
        REP (i, n) {
            gps[fnd(i)].eb(i);
            tmp++;
        }
        debug(itr++, gps.size());
        if (gps.size() == 1) {
            break;
        }

        for (const auto &v : gps) {
            for (int el : v.Y) {
                trie.erase(a[el]);
            }
            pair<int,int> bst = {0x3f3f3f3f, 0};
            for (int el : v.Y) {
                int res = trie.qry(a[el]);
                bst = min(bst, {res^a[el], res});
            }
            for (int el : v.Y) {
                trie.insert(a[el]);
            }

            if (mrg(v.X, rev[bst.Y])) {
                ans += bst.X;
            }
        }
    }
    cout << ans << endl;

}

