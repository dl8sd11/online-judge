#include <algorithm>
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
#ifdef tmdx
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

int n;
vector<pii> pts;
vector<int> x, y;

void sort_unique (vector<int> &vec) {
    sort(ALL(vec));
    vec.resize(unique(ALL(vec))-vec.begin());
}

struct PS { // prefix sum
    int sum[MAXN];

    PS () {
        memset(sum, 0, sizeof(sum));
    }

    void build () {
        int acc = 0;
        for (int i=0; i<MAXN; i++) {
            acc += sum[i];
            sum[i] = acc;
        }
    }

    int search (int p) {
        int l = -1, r = MAXN;
        while (l < r - 1) {
            int m = (l+r)>>1;
            if (sum[m] >= p) {
                r = m;
            } else {
                l = m;
            }
        }
        return r;
    }
} XP, YP;

double REVX (int id) {
    return x[id] + 0.5;
}
double REVY (int id) {
    return y[id] + 0.5;
}

struct S2D {
    struct Node {
        int l, r;
        Node *lc, *rc;
        int sum;

        void pull () {
            sum = 0;
            if (lc) {
                sum += lc->sum;
            }
            if (rc) {
                sum += rc->sum;
            }
        }
    };

    Node *root[MAXN];

    Node *add (int p, int val, Node *nd) {
        Node *nw = new Node(*nd);
        if (p == nd->l && p+1 == nd->r) {
            nw->sum += val;
            return nw;
        }

        int md = (nd->l + nd->r) >> 1;
        if (p >= md) {
            if (nw->rc == nullptr) {
                nw->rc = new Node({md, nd->r, 0, 0, 0});
            }
            nw->rc = add(p, val, nw->rc);
        } else {
            if (nw->lc == nullptr) {
                nw->lc = new Node({nd->l, md, 0, 0, 0});
            }
            nw->lc = add(p, val, nw->lc);
        }
        nw->pull();
        return nw;
    }

    int qry (int r, Node *nd) {
        if (!nd) {
            return 0;
        }
        if (nd->r == r) {
            return nd->sum;
        }
        int md = (nd->l + nd->r) >> 1;
        if (r >= md) {
            return qry(md, nd->lc) + qry(r, nd->rc);
        } else {
            return qry(r, nd->lc);
        }
    }

    void build() {
        sort(ALL(pts));

        int ptr = 0;
        root[0] = new Node({0, SZ(y), NULL, NULL, 0});
        for (int i=0; i<SZ(x); i++) {
            if (i) {
                root[i] = root[i-1];
            }
            while (ptr < n && pts[ptr].X == i) {
                root[i] = add(pts[ptr].Y, 1, root[i]);
                ptr++;
            }
        }
        assert(ptr == n);
    }
    int qry (int xx, int yy) {
        return qry(yy+1, root[xx]);
    }

} XY;

vector<int> perm(9);
bool check (int xl, int xr, int yl, int yr) {

    bool ans = true;

    int tot = perm[0];
    ans &= XY.qry(xl, yl) == tot;

    tot += perm[1];
    ans &= XY.qry(xl, yr) == tot;

    tot += perm[2];
    ans &= XY.qry(xl, SZ(y)-1) == tot;

    tot = perm[0] + perm[3];
    ans &= XY.qry(xr, yl) == tot;

    tot += perm[1] + perm[4];
    ans &= XY.qry(xr, yr) == tot;

    tot += perm[2] + perm[5];
    ans &= XY.qry(xr, SZ(y)-1) == tot;

    tot = perm[0] + perm[3] + perm[6];
    ans &= XY.qry(SZ(x)-1, yl) == tot;

    tot += perm[1] + perm[4] + perm[7];
    ans &= XY.qry(SZ(x)-1, yr) == tot;

    tot += perm[2] + perm[5] + perm[8];
    ans &= XY.qry(SZ(x)-1, SZ(y)-1) == tot;

    assert(tot == n);
    
    return ans;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    for (int i=0; i<n; i++) {
        int c, b;
        cin >> c >> b;
        pts.eb(c, b);
        x.eb(c);
        y.eb(b);
    }

    for (int i=0; i<9; i++) {
        cin >> perm[i];
    }
    sort_unique(x);
    sort_unique(y);

    for (auto &p : pts) {
        p.X = lower_bound(ALL(x), p.X) - x.begin();
        p.Y = lower_bound(ALL(y), p.Y) - y.begin();

        XP.sum[p.X]++;
        YP.sum[p.Y]++;
    }

    XP.build();
    YP.build();
    XY.build();

    sort(ALL(perm));
    do {
        int xl, xr, yl, yr;

        int sxl = perm[0] + perm[1] + perm[2];
        int sxr = sxl + perm[3] + perm[4] + perm[5];

        int syl = perm[0] + perm[3] + perm[6];
        int syr = syl + perm[1] + perm[4] + perm[7];
        
        debug(sxl, sxr, syl, syr);
        xl = XP.search(sxl);
        xr = XP.search(sxr);
        yl = YP.search(syl);
        yr = YP.search(syr);

        if (check(xl, xr, yl, yr)) {
            cout << fixed << setprecision(2) << REVX(xl) << " " <<REVX(xr) \
                << endl << REVY(yl) << " " << REVY(yr) << endl;
            return 0;
        }
    } while (next_permutation(ALL(perm)));
    cout << -1 << endl;

}

