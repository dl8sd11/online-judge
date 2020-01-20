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

const int MAXN = 100005;
const ll MOD = 1000000007;
const ll INF = 1e18 + 18;

int n;
ll k;
int a[MAXN], pos[MAXN], dp[MAXN];

struct Data {
    int mx;
    ll cnt;
};

Data mrg (const Data &s1, const Data &s2) {
    if (s1.mx == s2.mx) {
        return {s1.mx, min(INF,s1.cnt+s2.cnt)};
    } else {
        return s1.mx > s2.mx ? s1 : s2;
    }
}

struct Node {
    int l, r;
    Node *lc, *rc;
    Data dt;
    void pull () {
        dt = mrg(lc->dt, rc->dt);
    }
};
Node *root[MAXN];

Node *build (int l, int r) {
    if (r == l + 1) {
        return new Node{l, r, 0, 0, {0,0}};
    } else {
        int m = (l + r) >> 1;
        return new Node{l, r, build(l,m), build(m,r), {0,0}};
    }
}


Node *chg (int p, int val, ll cnt, Node *nd) {
    if (p >= nd->r || p < nd->l) {
        return nd;
    } else if (p == nd->l && p == nd->r - 1) {
        Node *ret = new Node(*nd);
        ret->dt = {val, cnt};
        return ret;
    } else {
        Node *ret = new Node(*nd);
        ret->lc = chg(p, val, cnt, ret->lc);
        ret->rc = chg(p, val, cnt, ret->rc);
        ret->pull();
        return ret;
    }
}

Data qry (int qL, int qR, Node *nd) {
    if (qL >= nd->r || qR <= nd->l || qL >= qR) {
        return (Data){0,0};
    } else if (qL <= nd->l && nd->r <= qR) {
        return nd->dt;
    } else {
        return mrg(qry(qL, qR, nd->lc), \
                   qry(qL, qR, nd->rc));
    }
}

vector<int> rev (vector<int> vec) {
    int ptr = 0;
    vector<int> ret;
    REP1 (i, n) {
        if (vec[ptr] == i) {
            ptr++;
        } else {
            ret.emplace_back(i);
        }
    }
    return ret;
}
/*********************GoodLuck***********************/
int main () {
    IOS();
    // #ifndef tmd

    // freopen("itout.in","r",stdin);
    // freopen("itout.out","w",stdout);

    // #endif // tmd
    cin >> n >> k;
    REP (i, n) {
        cin >> a[i];
        pos[a[i]] = i;
    }

    root[n+1] = build(0, n);
    debug("test");
    int len = 0;
    for (int i=n; i>=1; i--) {
        Data res = qry(pos[i]+1, n, root[i+1]);
        dp[i] = 1 + res.mx;
        len = max(len, dp[i]);
        root[i] = chg(pos[i],dp[i], max(1LL,res.cnt), root[i+1]);
        debug(qry(0,n,root[i]).cnt);
    }
    debug(dp[1]);

    vector<int> ans;

    int lst = -1;

    for (int i=1;i<=n;i++) {
        if (pos[i] <= lst) {
            ans.emplace_back(i);
        } else {
            Data res = qry(lst+1, n, root[i+1]);
            debug(res.mx, res.cnt, k);
            if (res.mx == len) {
                if (k <= res.cnt) {
                    ans.emplace_back(i);
                } else {
                    k -= res.cnt;
                    len--;
                    lst = pos[i];
                }
            } else {
                len--;
                lst = pos[i];
            }
        }
    }

    cout << SZ(ans) << endl;
    for (auto v : ans) {
        cout << v << endl;
    }
}
