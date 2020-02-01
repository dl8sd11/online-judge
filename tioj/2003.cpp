#include <vector>
#include <iostream>
#include <algorithm>
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

const int MAXN = 1000005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, m;

struct Edge {
    int h;
    vector<int> child;
};
vector<Edge> edge;

int djs[MAXN], id[MAXN];

void init() {
    REP (i, MAXN) {
        djs[i] = i;
        id[i] = i;
    }
}

int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

void mrg (int x, int y) {
    x = fnd(x), y = fnd(y);
    djs[max(x,y)] = min(x,y);
}

int idx;

vector<int> ans;
void dfs (int nd) {
    debug(nd);
    if (nd<=n) {
        ans.emplace_back(nd);
    } else {
        REP (i, SZ(edge[nd-n-1].child)) {
            dfs(edge[nd-n-1].child[i]);
        }
    }
}


/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> m;
    init();

    edge.reserve(m);
    ans.reserve(n);
    REP (i, m) {
        int h, deg;
        cin >> h >> deg;
        edge.push_back({h,{}});
        edge.back().child.reserve(deg);

        REP (j, deg) {
            int d;
            cin >> d;
            edge.back().child.emplace_back(d);
        }
    }


    sort(edge.begin(),edge.end(),[](Edge &e1, Edge &e2) {
            return e1.h < e2.h;
    });

    idx = n;
    for (auto &e : edge) {
        sort(e.child.begin(),e.child.end(), [](int i, int j){
           return fnd(i) < fnd(j);
        });


        idx++;
        int x = e.child.front();
        REP (i, SZ(e.child)) {
            int pd = id[fnd(e.child[i])];
            mrg(e.child[i], x);
            e.child[i] = pd;
        }
        id[fnd(x)] = idx;

    }


    REP1 (i, n) {
        if (fnd(i)==i) {
            dfs(id[i]);
        }
    }

//    while(ans.size() != n) {}

    REP (i, n) {
        cout << ans[i] << " \n"[i==n-1];
    }

}
