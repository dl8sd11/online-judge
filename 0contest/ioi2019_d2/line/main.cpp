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
template<typename T, typename S> ostream &operator << (ostream &os,const pair<T,S> &v){return os<<"{"<<v.X<<","<<v.Y<<"}";}
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
map<int,vector<int> > pts;

vector<pii> ones;
vector<pair<int,pair<int,int> > > lines;

vector<pii> ans;

pii cur = {0, 0};

void add (int x, int y) {
    if (ans.size() >= 2) {
        pii l1 = ans[ans.size()-2], l2 = ans[ans.size()-1];
        if (ans.back().X == x && l1.X == x) {
            if (l1.Y <= l2.Y && l2.Y <= y) {
                ans.pop_back();
            } else if (l1.Y >= l2.Y && l2.Y >= y) {
                ans.pop_back();
            }
        } else if (l2.Y == y && l1.Y == y) {
            if (l1.X <= l2.X && l2.X <= x) {
                ans.pop_back();
            } else if (l1.X >= l2.X && l2.X >= x) {
                ans.pop_back();
            }
        }
    }
    ans.eb(x, y);
}

void go (int x, int y) {
    if (cur.X != x) {
        add(x, cur.Y);
        cur.X = x;
    }

    if (cur.Y != y) {
        ans.eb(x, y);
        cur.Y = y;
    }
}

void go (pii p) {
    go(p.X, p.Y);
}

struct RMQMX {
    int seg[MAXN*2];
    int INF = -MOD;

    void build () {
        for (int i=n; i>0; i--) {
            seg[i] = max(seg[i<<1], seg[i<<1|1]);
        }
    }

    void chg (int x, int val) {
        for (seg[x+=n]=val;x>1;x>>=1) {
            seg[x>>1] = max(seg[x], seg[x^1]);
        }
    }

    int qry (int l, int r) {
        int res = INF;
        for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if (l&1) {
                res = max(res, seg[l++]);
            }
            if (r&1) {
                res = max(res, seg[--r]);
            }
        }
        return res;
    }
};

struct RMQMN {
    int seg[MAXN*2];
    int INF = MOD;

    void build () {
        for (int i=n; i>0; i--) {
            seg[i] = min(seg[i<<1], seg[i<<1|1]);
        }
    }

    void chg (int x, int val) {
        for (seg[x+=n]=val;x>1;x>>=1) {
            seg[x>>1] = min(seg[x], seg[x^1]);
        }
    }

    int qry (int l, int r) {
        int res = INF;
        for (l+=n, r+=n; l<r; l>>=1, r>>=1) {
            if (l&1) {
                res = min(res, seg[l++]);
            }
            if (r&1) {
                res = min(res, seg[--r]);
            }
        }
        return res;
    }
};


RMQMN mn;
RMQMX mx;

vector<int> ad () {
    vector<int> res = {};

    int lst = -1;
    int lim = -MOD + 1;
    while (true) {
        int L = -1, R = n;
        if (res.size()) {
            L = res.back();
        }
        int bs = L + 1;
        while (L < R - 1) {
            int M = (L + R) >> 1;
            if (mx.qry(bs, M+1) >= lim) {
                R = M;
            } else {
                L = M;
            }
        }
        if (R == n) {
            break;
        }

        lim = ones[R].Y;
        res.eb(R);
    }
    return res;
}

vector<int> dd () {
    vector<int> res = {};

    int lst = -1;
    int lim = MOD - 1;
    while (true) {
        int L = -1, R = n;
        if (res.size()) {
            L = res.back();
        }
        int bs = L + 1;
        while (L < R - 1) {
            int M = (L + R) >> 1;
            if (mn.qry(bs, M+1) <= lim) {
                R = M;
            } else {
                L = M;
            }
        }
        if (R == n) {
            break;
        }

        lim = ones[R].Y;
        res.eb(R);
    }
    return res;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    for (int t=1; t<=10; t++) {
        string dg = "0";
        dg += char(t+'0');
        cur = {0, 0};

        string fn = (t<10?dg:"10");
        freopen(("tests/" + fn + ".in").c_str(), "r", stdin);
        freopen(("sig/" + fn + ".out").c_str(), "w", stdout);
        pts.clear();
        ones.clear();
        lines.clear();

        cin >> n;
        REP (i, n) {
            int x, y;
            cin >> x >> y;
            pts[x].eb(y);
        }

        for (auto v : pts) {
            if (true || v.Y.size() == 1) {
                ones.eb(v.X, v.Y[0]);
            } else {
                int mn = MOD, mx = -MOD;
                for (auto u : v.Y) {
                    mn = min(mn, u);
                    mx = max(mx, u);
                }
                lines.eb(v.X, pii(mn, mx));
            }
        }
        sort(ALL(ones));
//        debug(ones);

        ans.clear();
        for (auto v : lines) {
            ans.eb(v.X, (cur.Y == 0 ? 0 : 1000000000));
            ans.eb(v.X, (cur.Y == 0 ? 1000000000 : 0));
            cur = {v.X, 1000000000 - cur.Y};
        }
//        debug(SZ(ans));

        n = ones.size();
        for (int i=0; i<n; i++) {
            mn.seg[i+n] = ones[i].Y;
            mx.seg[i+n] = ones[i].Y;
        }
        mx.build();
        mn.build();

        int rem = 0;

        while (rem < ones.size()) {

            vector<int> ac = ad();
            vector<int> dc = dd();

//            debug(ones);
//            debug(ac);
//            debug(dc);

            if (ac.size() > dc.size()) {
                rem += SZ(ac);

                go(ones[ac[0]]);
                for (int i=1; i<SZ(ac); i++) {
                    if (i&1) {
                        go(ones[ac[i]].X, ones[ac[i-1]].Y);
                    } else {
                        go(ones[ac[i-1]].X, ones[ac[i]].Y);
                    }
                }
                go(ones[ac.back()]);


                for (int i=0; i<SZ(ac); i++) {
                    mn.chg(ac[i], MOD);
                    mx.chg(ac[i], -MOD);
                }

            }
            else {

                rem += SZ(dc);

                go(ones[dc[0]]);
                for (int i=1; i<SZ(dc); i++) {
                    if (i&1) {
                        go(ones[dc[i]].X, ones[dc[i-1]].Y);
                    } else {
                        go(ones[dc[i-1]].X, ones[dc[i]].Y);
                    }
                }
                go(ones[dc.back()]);


                for (int i=0; i<SZ(dc); i++) {
                    mn.chg(dc[i], MOD);
                    mx.chg(dc[i], -MOD);
                }
            }

        }


        cout << SZ(ans) << endl;
        cerr << SZ(ans) << endl;
        for (auto v : ans) {
            cout << v.X << " " << v.Y << endl;
        }

    }

}
/*
8
80 32
59 15
22 84
54 47
53 28
68 40
60 11
61 100


*/
