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
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, t;
pair<int,int> pt[MAXN];
struct Line {
    bool hori;
    int xf, yf, xs, ys, id;

    Line(int _x1, int _y1, int _x2, int _y2, int _id) {
        hori = _y1 == _y2;
        xf = _x1;
        yf = _y1;
        xs = _x2;
        ys = _y2;
        id = _id;
        if (xf > xs || yf > ys) {
            swap(xf, xs);
            swap(yf, ys);
        }
    }
};
vector<Line> line;

ll ans;

struct Query {
    int add, x, l, r, id;
};
ostream &operator << (ostream &os, const Query &q) {
    return os << "{" << q.add << "," << q.x << "," << q.l << "," << q.r << "," << q.id << "}";
}
vector<Query> query;

bool byId (const Query &q1, const Query &q2) {
    return q1.id < q2.id;
}

bool byX (const Query &q1, const Query &q2) { // query first
    if (q1.x != q2.x) {
        return q1.x < q2.x;
    } else {
        return abs(q1.add) > abs(q2.add);
    }
}

int bit[MAXN];

void add (int x, int val) {
    for (;x<MAXN;x+=-x&x) {
        bit[x] += val;
    }
}

int qry (int x) {
    int ret = 0;
    for (;x>0;x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

void CDQ (int L, int R) {
    debug(L, R);
    if (query[L].x == query[R-1].x) {
        return;
    }
    int xM = (query[L].x + query[R-1].x) >> 1, M;
    for (M=L;M<R;M++) {
        if (query[M].x > xM) {
            break;
        }
    }
    CDQ(L, M);
    CDQ(M, R);

    sort(query.begin()+L, query.begin()+M, byId);
    sort(query.begin()+M, query.begin()+R, byId);

    int j = L;
    debug(L, R, M);

    vector<int> did;
    for (int i=M; i<R; i++) {
        while (j<M && query[j].id + t <= query[i].id) {
            if (query[j].add == 0) {
                    debug(query[j]);
                add(query[j].l+1, 1);
                add(query[j].r, -1);
                did.emplace_back(j);
            }
            j++;
        }
        if (query[i].add != 0) {
            int res = qry(query[i].l);
            debug(query[i], res);
            ans += res * query[i].add;
        }
    }

    for (int i : did) {
        add(query[i].l+1, -1);
        add(query[i].r, 1);
    }

    sort(query.begin()+L, query.begin()+R, byX);
}

vector<int> xval;

int getX (int x) {
    return lower_bound(xval.begin(),xval.end(),x)-xval.begin()+1;
}

void solve () {
    query.clear();
    xval.clear();
    for (Line l : line) {
        xval.emplace_back(l.xf);
        xval.emplace_back(l.xs);
    }
    sort(xval.begin(),xval.end());
    xval.resize(unique(xval.begin(),xval.end())-xval.begin());

    for (Line l : line) {
        if (l.hori) {
            query.push_back({0, l.yf, getX(l.xf), getX(l.xs), l.id});
        } else {
            query.push_back({1, l.ys, getX(l.xf), getX(l.xs), l.id});
            query.push_back({-1, l.yf+1, getX(l.xf), getX(l.xs), l.id});
        }
    }

    sort(query.begin(), query.end(), byX);
    debug(query);
    CDQ(0, SZ(query));
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    #ifndef tmd

    freopen("mowing.in","r",stdin);
    freopen("mowing.out","w",stdout);

    #endif // tmd
    cin >> n >> t;

    REP (i, n) {
        cin >> pt[i].first >> pt[i].second;
        if (i > 0) {
            line.emplace_back(pt[i-1].first,pt[i-1].second,pt[i].first,pt[i].second, i);
        }
    }

    solve();
    for (auto &l : line) {
        l.hori ^= 1;
        swap(l.xf, l.yf);
        swap(l.xs, l.ys);
    }
    solve();

    cout << ans << endl;
}
/*
5 2
1 0
1 5
5 5
5 3
0 3
*/
