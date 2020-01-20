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

const int MAXN = 40321;
const ll MOD = 1000000007;
const int INF = 0x3f3f3f3f;

int t;
int n, s, m, d;
vector<int> edge[MAXN];

int disS[MAXN], disM[MAXN];
void build(int *dis, int st) {
    memset(dis, INF, 4*MAXN);
    dis[st] = 0;
    queue<int> bfs;
    bfs.emplace(st);
    while (bfs.size()) {
        int cur = bfs.front();
        bfs.pop();

        for (auto v : edge[cur]) {
            if (dis[v] == INF) {
                dis[v] = dis[cur] + 1;
                bfs.emplace(v);
            }
        }
    }
}

int getID (vector<int> &perm, int cur) {
    return lower_bound(perm.begin(), perm.end(), cur)-perm.begin();
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> n >> s >> m >> d;
        vector<int> perm(n);
        iota(perm.begin(),perm.end(), 1);

        vector<int> state;

        do {
            int sum = 0;
            for (auto v : perm) {
                sum = sum * 10 + v;
            }
            state.emplace_back(sum);
        } while (next_permutation(perm.begin(), perm.end()));

        int pw = 1;
        REP (i, n-1) {
            pw *= 10;
        }

        for (auto v : state) {
            int tp = v / pw;
            int org = v;
            v -= tp * pw;

            int xx = 1;
            for (int i=0; i<n-1; i++) {
                int nw = v;
                int tmp = nw / xx*xx;
                nw = (nw - tmp) + tp*xx + tmp*10;
                xx *= 10;
                edge[getID(state,org)].emplace_back(getID(state,nw));
            }
        }

        build(disS, getID(state, s));
        build(disM, getID(state, m));

        int cnt = 0;
        int bs = disS[getID(state,m)];
        REP (i, SZ(state)) {
            if (disS[i] == d && bs+disM[i] == d) {
                cnt++;
            }
            edge[i].clear();
        }

        cout << cnt << endl;
    }

}
/*
2
3 123 231 2
*/
