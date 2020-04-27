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

const int MAXN = 1003;
const ll MOD = 1000000007;
const int MAXC = MAXN*MAXN*3;

int n, m;
int len[2][MAXN];
bool tp[2][MAXN];

struct Line {
    int p, l, r;

    bool operator < (const Line &oth) const {
        return p < oth.p;
    }
};
ostream& operator << (ostream &os, const Line &p) {
    return os << "{" << p.l << " " << p.r << " " << p.p << "}";
}

struct RMQ {
    int seg[MAXC*2]; 
    int cnt[MAXC];
    int sz;

    void clear(int _sz) {
        sz = _sz + 2;
        memset(seg, -1, sizeof(int) * sz * 2);
        memset(cnt, 0, sizeof(int) * sz);
    }

    int qry (int l, int r) {
        int ret = -1;
        for (l+=sz, r+=sz; l<r; l>>=1, r>>=1) {
            if (l&1) {
                ret = max(ret, seg[l++]);
            }
            if (r&1) {
                ret = max(ret, seg[--r]);
            }
        }
        return ret;
    }
    void chg (int x, int val) {
        for (seg[x+=sz]=val; x>1; x>>=1) {
            seg[x>>1] = max(seg[x], seg[x^1]); 
        }
    }
    void add (int x, int val) {
        cnt[x] += val;
        debug(x, val, cnt[x]);
        if (cnt[x] == 0) {
            chg(x,-1);
        } else if (cnt[x] == 1) {
            chg(x, x);
        }
    }
};
RMQ rmq;

struct Query {
    int add;
    int l, r;

    bool operator < (const Query &oth) const {
        return add > oth.add;
    }
};
vector<Query> query[MAXC];

void suni (vector<int> &vec) {
    sort(ALL(vec));
    vec.resize(unique(ALL(vec))-vec.begin());
}
// TODO border case: all same color
int ans = 0;

int msec (pii p1, pii p2) {
    if (p1.Y < p2.X || p2.Y < p1.X) {
        return -1;
    } else {
        return min(p1.Y, p2.Y);
    }
}

void total () {

    for (int b=0; b<2; b++) {

        int ws0 = 0, bs0 = 0;
        for (int i=0 ;i<n; i++) {
            if (tp[b][i]) {
                ws0 += len[b][i];
            } else {
                bs0 += len[b][i];
            }
        }

        for (int i=0; i<m; i++) {
            int w = 0, B = 0;

            if (i) {
                int dw = 0, db = 0;
                dw += len[!b][i-1];
                db += len[!b][i];
                if (!tp[!b][i-1]) {
                    swap(dw, db);
                }

                if (ws0 <= dw && bs0 <= db) {
                    ans = max(ans, ws0 + bs0);
                }
            }
            for (int j=i; j<m; j++) {
                int dw = 0, db = 0;

                if (tp[!b][j]) {
                    w += len[!b][j];
                    db += len[!b][j+1];
                } else {
                    B += len[!b][j];
                    dw += len[!b][j+1];
                }
                debug(i, j, w, B);

                if (tp[!b][i]) {
                    db += i ? len[!b][i-1] : 0;
                } else {
                    dw += i ? len[!b][i-1] : 0;
                }
                

                if (bs0 >= B && bs0 <= B + db) {
                    if (ws0 >= w && ws0 <= w + dw) {
                        debug(b, i, j, bs0, ws0, w, B, dw, db);
                        ans = max(ans, bs0 + ws0);
                    }
                }
            }
        }

        swap(n, m);
        

    }

}
void solve () {

    vector<Line> xline, yline;
    for (int i=0; i<n; i++) {
        int b = 0, w = 0;
        for (int j=i; j<n; j++) {

            if (tp[0][j] == 0) {
                b += len[0][j];
                xline.push_back({b, w, w+len[0][j+1]});
            } else {
                w += len[0][j];
            }

        }
    }

    for (int i=0; i<m; i++) {
        int b = 0, w = 0;

        for (int j=i; j<m; j++) {

            if (tp[1][j] == 0) {
                b += len[1][j];
            } else {
                w += len[1][j];
                yline.push_back({w, b, b+len[1][j+1]});
            }

        }
    }

    debug(xline);
    debug(yline);

    vector<int> xval, yval;
    for (auto v : xline) {
        xval.eb(v.l);
        xval.eb(v.r);
        yval.eb(v.p);
    }

    for (auto v : yline) {
        yval.eb(v.l);
        yval.eb(v.r);
        xval.eb(v.p);
    }

    suni(xval);
    suni(yval);

    int mx = 0;
    for (auto &v : xline) {
        v.l = lower_bound(ALL(xval), v.l) - xval.begin();
        v.r = lower_bound(ALL(xval), v.r) - xval.begin();

        v.p = lower_bound(ALL(yval), v.p) - yval.begin();


        query[v.l].push_back({1, v.p, 0});
        query[v.r].push_back({-1, v.p, 0});

        mx = max(mx, v.l);
        mx = max(mx, v.r);
    }

    for (auto &v : yline) {
        v.l = lower_bound(ALL(yval), v.l) - yval.begin();
        v.r = lower_bound(ALL(yval), v.r) - yval.begin();

        v.p = lower_bound(ALL(xval), v.p) - xval.begin();

        query[v.p].push_back({0, v.l, v.r});
        mx = max(mx, v.p);
    }

    rmq.clear(yval.size());

    for (int i=0; i<=mx; i++) {
        sort(ALL(query[i]));
        for (auto q : query[i]) {

            if (q.add == 0) {
                int cur = rmq.qry(q.l, q.r+1);
                if (cur >= 0) {

                    debug("HEY",xval[i], q.l, q.r, yval[cur], cur);
                    ans = max(ans, xval[i] + yval[cur]);
                }
            } else {
                rmq.add(q.l, q.add);
                debug(xval[i], q.l);
            }
        }
        query[i].clear();
    }

    


}
void flip () {
    for (int t=0; t<2; t++) {
        for (int i=0; i<max(n,m); i++) {
            tp[t][i] ^= 1;
        }
    }
}

void rev (int d) {
    reverse(len[d], len[d]+(d?m:n));
    reverse(tp[d],tp[d]+(d?m:n));
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

    int mxb[2][2] = {};
    for (int i=0; i<n; i++) {
        char c;
        cin >> c >> len[0][i];
        tp[0][i] = c == 'W';

        mxb[0][tp[0][i]] = max(mxb[0][tp[0][i]], len[0][i]);;
    }

    cin >> m;

    for (int i=0; i<m; i++) {
        char c;
        cin >> c >> len[1][i];
        tp[1][i] = c == 'W';

        mxb[1][tp[1][i]] = max(mxb[1][tp[1][i]], len[1][i]);
    }

    debug(mxb[0][0], mxb[0][1], mxb[1][0], mxb[1][1]);
    ans = max(min(mxb[0][1], mxb[1][1]), min(mxb[0][0], mxb[1][0]));

    for (int i=0; i<2; i++) {
        for (int j=0; j<2; j++) {

            solve();
            flip();
            solve();

            rev(0);
        }
        rev(1);
    }

    total();
    cout << ans << endl;
}

/*
 3
 T 5
 W 7
 T 4
 3
 W 6
 T 6
 W 6
*/
