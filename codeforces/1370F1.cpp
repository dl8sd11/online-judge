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
#define debug(...)
#define pary(...)
#endif

const int MAXN = 1003;
const ll MOD = 1000000007;

int n, m;
vector<int> edge[MAXN];

pair<int,int> qry (vector<int> elm) {
    cout << "? " << SZ(elm);

    for (auto e : elm) {
        cout << " " << e;
    }
    cout << endl;

    int x, d;
    cin >> x >> d;
    return {x, d};
}

void gen (int nd, int par, int dep, vector<int> &res) {
    if (dep == 0) {
        res.eb(nd);
        return;
    }
    for (auto v : edge[nd]) {
        if (v != par) {
            gen(v, nd, dep-1, res);
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    int t;
    cin >> t;
    while (t--) {
        cin >> n;

        for (int i=0, u, v; i<n-1; i++) {
            cin >> u >> v;
            edge[u].eb(v);
            edge[v].eb(u);
        }

        int x, y, d, d2;
        vector<int> vec(n);
        iota(ALL(vec), 1);
        tie(x, d) = qry(vec);
        debug(x, d);

        tie(y, d2) = qry(edge[x]);
        assert(d == d2);

        int l = 0, r = n;
        while (l < r - 1) {
            int mid = (l + r) >> 1;
            vector<int> nds;
            gen(x, y, mid, nds);

            if (nds.empty()) {
                r = mid;
            } else if (qry(nds).Y == d2) {
                l = mid;
            } else {
                r = mid;
            }
        }

        vector<int> ls, rs;
        gen(x, y, l, ls);
        gen(y, x, d-l-1, rs);
        debug(ls, rs, l, d-l-1);

        x = qry(ls).X;
        y = qry(rs).X;
        cout << "! " << x << " " << y << endl;

        string ans;
        cin >> ans;
        assert(ans == "Correct");

        for (int i=1; i<=n; i++) {
            edge[i].clear();
        }
    }


}

