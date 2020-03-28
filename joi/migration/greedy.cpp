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

const int MAXN = 302;
const ll MOD = 1000000007;

int n, m, l;
set<int> G[MAXN];
vector<pii> pos;
set<int> id;

set<int> used;
int ans[MAXN];

struct Segment {
    pii st, ed;
};

pii operator- (const pii &p1, const pii &p2) {
    return {p1.X - p2.X, p2.Y - p2.Y};
}

int cross (pii a, pii b) {
    ll res = 1LL*a.X*b.Y - 1LL*a.Y*b.X;
    return res / abs(res);
}

bool inter (Segment &s1, Segment &s2) {
    bool b1 = cross(s1.st-s1.ed, s2.st-s1.ed) != cross(s1.st-s1.ed, s2.ed-s1.ed);
    bool b2 = cross(s2.st-s2.ed, s1.st-s2.ed) != cross(s2.st-s2.ed, s1.ed-s2.ed);
    return b1 && b2;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;

    for (int i=0; i<m; i++) {
        int u, v;
        cin >> u >> v;
        G[u].insert(v);
        G[v].insert(u);
    }

    cin >> l;

    for (int i=0; i<l; i++) {
        int x, y;
        cin >> x >> y;
        pos.eb(x, y);
        id.emplace(i+1);
    }

    vector<int> nid;
    REP (i, n) {
        nid.emplace_back(i);
    }
    random_shuffle(ALL(nid));


    vector<Segment> prv;

    for (int i=0; i<n; i++) {
        int ptid = 0;
        int bst = MOD;

        for (auto v : id) {


            vector<Segment> nw;
            for (auto u : used) {
                if (G[nid[i]].count(u)) {
                    nw.push_back(Segment{pos[v], pos[ans[u]]});
                }
            }

            int cur = 0;
            for (auto s1 : prv) {
                for (auto s2 : nw) {
                    cur += inter(s1, s2);
                }
            }

            if (cur < bst) {
                ptid = v;
                bst = cur;
            }
        }

        for (auto u : used) {
            if (G[nid[i]].count(u)) {
                prv.push_back({pos[ptid], pos[ans[u]]});
            }
        }

        debug(ptid, bst);
        ans[nid[i]] = ptid;
        id.erase(ptid);
        used.insert(nid[i]);
    }

    for (int i=0; i<n; i++) {
        cout << ans[i] << endl;
    }

}
