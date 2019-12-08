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

int n, m, ans[MAXN];
vector<int> pos[MAXN];
typedef pair<int,int> pii;
pii query[MAXN];

struct Search {
    int L, R;
    vector<int> id;
};

int bit[MAXN];
void add (int x, int val) {
    for (x++;x<MAXN; x+=-x&x) {
        bit[x] += val;
    }
}

int qry (int x) {
    int ret = 0;
    for (x++;x>0; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

int qry (int l, int r) {
    r = min(n-1, r);
    l = max(0, l);
    return qry(r) - (l ? qry(l-1) : 0);
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    REP (i, n) {
        int b;
        cin >> b;
        pos[b].emplace_back(i);
    }

    REP (i, m) {
        cin >> query[i].first >> query[i].second;
    }

    Search root;
    root.L = 0, root.R = n;
    root.id.resize(m);
    iota(root.id.begin(), root.id.end(), 0);

    queue<Search> que;
    que.emplace(root);

    int lst = 0;
    while (!que.empty()) {
        Search cur = que.front();
        que.pop();
        if (cur.L == cur.R - 1) {
            for (auto id : cur.id) {
                ans[id] = cur.R;
            }
            continue;
        }
        debug(cur.L, cur.R, cur.id);

        int mid = (cur.L + cur.R) >> 1;

        if (lst > mid) {
            memset(bit, 0, sizeof(bit));
            lst = 0;
        }
        while (lst<n && lst<=mid) {
            for (auto v : pos[lst]) {
                add(v, 1);
            }
            debug(lst);
            lst++;
        }
        debug(lst);

        vector<int> Lid, Rid;
        for (auto idx : cur.id) {
            if (qry(query[idx].first-mid, query[idx].first+mid) >= query[idx].second) {
                Lid.emplace_back(idx);
            } else {
                Rid.emplace_back(idx);
            }
        }

        que.push({cur.L, mid, Lid});
        que.push({mid, cur.R, Rid});
    }

    REP (i, m) {
        cout << ans[i] << endl;
    }

}
