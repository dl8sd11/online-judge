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
const int MAXLG = __lg(MAXN);
const ll MOD = 1000000007;

int n, q;
vector<pair<int,int> > edge[MAXN];

int anc[MAXLG][MAXN], dep[MAXN], st[MAXN], edge_cnt, a[MAXN*2];
int w[MAXN];
void dfs (int nd, int par) {
    anc[0][nd] = par;
    st[nd] = edge_cnt;
    dep[nd] = dep[par] + 1;

    for (auto v : edge[nd]) {
        if (v.first != par) {
            a[++edge_cnt] = v.second;

            dfs(v.first, nd);

            a[++edge_cnt] = v.second;
        }
    }
}

const int K = 336;
struct Query {
    int l, r, bid, qid;
    bool operator < (const Query &oth) const {
        if (bid != oth.bid) {
            return bid < oth.bid;
        } else {
            return r < oth.r;
        }
    }

    Query (int L, int R, int id) {
        l = L, r = R, qid = id;
        bid = l/K;
    }
};

vector<Query> query;
ll cur_ans, ans[MAXN];
int cnt[MAXN], occ[MAXN];
bool used[MAXN];

void calc (int c, int dl) {
    if (c <= 0) {
        return;
    }
    if (c % 2 == 0) {
        cur_ans += dl * (occ[c/2]);
    }
    if (c * 2 < MAXN) {
        cur_ans += dl * (occ[c*2]);
    }
}

void add (int eid) {
    debug(eid);//return;
    int W = w[eid];
    int &C = cnt[W];
    calc(C, -1);

    occ[C]--;
    C++;
    occ[C]++;

    calc(C, 1);
}

void sub (int eid) {
    debug(eid);//return;
    int W = w[eid];
    int &C = cnt[W];
    calc(C, -1);

    occ[C]--;
    C--;
    occ[C]++;

    calc(C, 1);
}

void chg (int i) {
    int id = a[i];
    if (!used[id]) {
        used[id] = true;
        add(id);
    } else {
        used[id] = false;
        sub(id);
    }
}

/*********************GoodLuck***********************/
int main () {
    IOS();
    cin >> n >> q;
    REP (i, n-1) {
        int u, v, W;
        cin >> u >> v >> W;
        edge[u].emplace_back(v, i);
        edge[v].emplace_back(u, i);
        w[i] = W;
    }

    dfs(1, 0);
    pary(st+1,st+1+n);


    REP (i, q) {
        int u, v;
        cin >> u >> v;

        query.emplace_back(min(st[u],st[v])+1,max(st[u],st[v]),i);
    }

    sort(query.begin(),query.end());

    for (int i=0,L=1,R=0;i<q;i++) {
        debug(L, R);
        debug(query[i].l, query[i].r,query[i].qid);
        while (R < query[i].r) {
            R++;
            chg(R);
        }
        while (R > query[i].r) {
            chg(R);
            R--;
        }
        while (L > query[i].l) {
            --L;
            chg(L);
        }
        while (L < query[i].l) {
            chg(L);
            ++L;
        }
        ans[query[i].qid] = cur_ans;
    }

    REP (i, q) {
        cout << ans[i] << endl;
    }
}
