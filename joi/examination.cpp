#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#ifdef tmdd
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
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, q;

struct Query {
    int id;
    int x, y, z;
};

ostream &operator << (ostream &os, Query &q) {
    return os << "{" << q.id << ":" << q.x << "," << q.y << "," << q.z << "}";
}

bool byZ (const Query &q1, const Query &q2) {
    return q1.z < q2.z;
}

bool byX (const Query &q1, const Query &q2) {
    return q1.x < q2.x;
}
Query qry[MAXN];
int ans[MAXN];

int bit[MAXN];

void add (int x, int val) {
    for (x++;x<MAXN;x+=-x&x) {
        bit[x] += val;
    }
}

int sum (int x) {
    int ret = 0;
    for (x++;x>0;x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

void solve (int l, int r) {
//    cerr << l << " " << r << " " << qry[l].z << " " << qry[r-1].z << endl;
//    if (l == r) {
//        for (int i=l-10;i<r+10;i++) {
//            cerr<<qry[i] << endl;
//        }
//    }
    assert(l != r);
    if (qry[l].z == qry[r-1].z) {
        return;
    } else {
        int mid = (qry[l].z + qry[r-1].z) >> 1;
        int m;
        for (m=l;m<r;m++) {
            if (qry[m].z > mid) {
                break;
            }
        }

        solve(l,m);
        solve(m,r);

        sort(qry+l,qry+m,byX);
        sort(qry+m,qry+r,byX);

        debug(l, m, r);
        pary(qry+l, qry+m);
        pary(qry+m, qry+r);


        vector<int> opr;

        int rid = r-1;
        for (int i=m-1;i>=l;i--) {
            while (rid>=m&&qry[rid].x>=qry[i].x) {
                if (qry[rid].id == -1) {
                    add(qry[rid].y, 1);
                    opr.emplace_back(qry[rid].y);
                }
                rid--;
            }
            if (qry[i].id != -1) {
                int dl = sum(MAXN-2) - sum(qry[i].y-1);
                ans[qry[i].id] += dl;
            }
        }

        for (auto id : opr) {
            add(id, -1);
        }

        sort(qry+l,qry+r,byZ);
    }
}


vector<int> yval;
/*********************GoodLuck***********************/
signed main () {
    IOS();

    cin >> n >> q;

    REP (i, n) {
        #ifdef tmd
        qry[i].x = rand()%MOD;
        qry[i].y = rand()%MOD;
        #else
        cin >> qry[i].x >> qry[i].y;
        #endif
        qry[i].z = qry[i].x+qry[i].y+1;
        qry[i].id = -1;
        yval.emplace_back(qry[i].y);
    }

    for (int i=n;i<n+q;i++) {
        #ifdef tmd
        qry[i].x = rand()%MOD;
        qry[i].y = rand()%MOD;
        qry[i].z = rand();
        #else
        cin >> qry[i].x >> qry[i].y >> qry[i].z;
        #endif
        qry[i].id = i-n;
        yval.emplace_back(qry[i].y);
    }

    sort(yval.begin(),yval.end());
    yval.resize(unique(yval.begin(),yval.end())-yval.begin());
    for (int i=0;i<n+q;i++) {
        qry[i].y = lower_bound(yval.begin(),yval.end(),qry[i].y)-yval.begin();
    }
    debug("en d");


    sort(qry,qry+n+q,byZ);
    pary(qry,qry+n+q);
    solve(0, n+q);
    REP (i, q) {
        cout << ans[i] << endl;
    }
}
