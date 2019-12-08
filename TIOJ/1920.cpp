#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
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

const int MAXN = 10004;
const ll MOD = 1000000007;

struct Trie {
    int cnt;
    Trie* child[2];
    Trie () {
        cnt = 0;
        child[0] = child[1] = nullptr;
    }

    void pull () {
        cnt = 0;
        if (child[0]) {
            cnt += child[0]->cnt;
        }
        if (child[1]) {
            cnt += child[1]->cnt;
        }
    }
};

Trie* root[MAXN];
Trie* add (Trie*nd, int num, int k) {
    Trie* ret = new Trie(*nd);
    if (k == -1) {
        ret->cnt++;
        return ret;
    }

    if (num & (1<<k)) {
        if (ret->child[1] == nullptr) {
            ret->child[1] = new Trie();
        }
        ret->child[1] = add(ret->child[1], num, k-1);
    } else {
        if (ret->child[0] == nullptr) {
            ret->child[0] = new Trie();
        }
        ret->child[0] = add(ret->child[0], num, k-1);
    }
    ret->pull();
    return ret;
}

int getCnt (Trie* nd) {
    return nd ? nd->cnt : 0;
}

Trie* getChild (Trie *nd, int id) {
    return nd ? nd->child[id] : nullptr;
}

int qry (Trie* H, Trie* L, int target, int k) {
    if (k == -1) {
        return 0;
    }
    Trie *L0 = getChild(L, 0), *L1 = getChild(L, 1);
    Trie *H0 = getChild(H, 0), *H1 = getChild(H, 1);

    if (getCnt(H0) - getCnt(L0) == 0) {
        return qry(H1, L1, target, k-1) ^ (1<<k);
    }
    if (getCnt(H1) - getCnt(L1) == 0) {
        return qry(H0, L0, target, k-1);
    }

    int rev = 1 ^ ((target>>k) & 1);

    return qry(getChild(H,rev), getChild(L,rev), target, k-1) ^ (rev<<k);

}


int a[MAXN], p[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();
    int n, q;
    cin >> n >> q;
    REP (i, n) {
        cin >> a[i];
    }

    root[n] = new Trie();
    for (int i=n-1; i>=0; i--) {
        p[i] = p[i+1] ^ a[i];
        root[i] = add(root[i+1], p[i], 30);
        assert(root[i]->cnt == n-i);
    }

    while (q--) {
        int l, r, v;
        cin >> l >> r >> v;
        v = v ^ p[r];
        cout << (qry(root[l], root[r], v, 30) ^ v) << endl;
    }

}

