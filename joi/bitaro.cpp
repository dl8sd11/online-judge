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
template<typename T> ostream &operator << (ostream &os,pair<T,T> &v){return os<<"{"<<v.first<<","<<v.second<<"}";}
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
const int K = sqrt(100005);

int n, m, q;
vector<int> edge[MAXN], redge[MAXN];
bool ban[MAXN];
vector<pair<int,int> > bst[MAXN];

bool used[MAXN];
void mrg (int to, int from) {
    vector<pair<int,int> > res;

    int ti = 0, fi = 0;
    while (res.size() < K && (ti < SZ(bst[to]) || fi < SZ(bst[from]))) {
        if (ti == SZ(bst[to])) {
            if (!used[bst[from][fi].first]) {
                used[bst[from][fi].first] = true;
                res.emplace_back(bst[from][fi]);
            }
            fi++;
        } else if (fi == SZ(bst[from])) {
            if (!used[bst[to][ti].first]) {
                used[bst[to][ti].first] = true;
                res.emplace_back(bst[to][ti]);
            }
            ti++;
        } else {
            if (bst[from][fi].second > bst[to][ti].second) {
                if (!used[bst[from][fi].first]) {
                    used[bst[from][fi].first] = true;
                    res.emplace_back(bst[from][fi]);
                }
                fi++;
            } else {
                if (!used[bst[to][ti].first]) {
                    used[bst[to][ti].first] = true;
                    res.emplace_back(bst[to][ti]);
                }
                ti++;
            }
        }
    }
    for (auto p : res) {
        used[p.first] = false;
    }
    bst[to] = res;
}

void build () {
    for (int i=1; i<=n; i++) {
        bst[i].emplace_back(i, -1);
        for (auto v : redge[i]) {
            mrg(i, v);
        }
        for (auto &el : bst[i]) {
            el.second++;
        }
    }
}

int qrySmall (int root) {
    int ans = -1;
    for (auto v : bst[root]) {
        if (!ban[v.first]) {
            ans = max(ans, v.second);
        }
    }
    return ans;
}

int dp[MAXN];
int qryBig (int root) {
    for (int i=1;i<=root;i++) {
        dp[i] = ban[i] ? -1 : 0;
        for (auto v : redge[i]) {
            if (dp[v] != -1) {
                dp[i] = max(dp[i], dp[v]+1);
            }
        }
    }
    return dp[root];
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m >> q;
    REP (i, m) {
        int f, t;
        cin >> f >> t;
        edge[f].emplace_back(t);
        redge[t].emplace_back(f);
    }
    build();

    while (q--) {
        int nd, sz;
        cin >> nd >> sz;

        vector<int> banList;
        REP (i, sz) {
            int v;
            cin >> v;
            ban[v] = true;
            banList.emplace_back(v);
        }

        if (sz >= K) {
            cout << qryBig(nd) << endl;
        } else {
            cout << qrySmall(nd) << endl;
        }

        for (auto v : banList) {
            ban[v] = false;
        }
    }
}
