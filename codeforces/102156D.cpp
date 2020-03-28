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

const int MAXN = 5063;
const ll MOD = 1000000007;

struct Element {
    int color;
    ll zvec;
    bool inSet;
} element[MAXN];

struct MatroidZVector {
    ll basis[61];

    MatroidZVector () {
        memset(basis, -1, sizeof(basis));
    }

    void insert (ll vec) {
        for (int i=60; i>=0; i--) {
            if ((vec>>i) & 1) {
                if (basis[i] == -1) {
                    basis[i] = vec;
                    return;
                }
                vec ^= basis[i];
            }
        }
    }

    bool check (ll vec) {
        for (int i=60; i>=0; i--) {
            if ((vec>>i) & 1) {
                if (basis[i] == -1) {
                    return true;
                }
                vec ^= basis[i];
            }
        }
        return false;
    }
};

struct MatroidColor {
    int cnt[122];

    MatroidColor () {
        memset(cnt, 0, sizeof(cnt));
    }

    void insert (int c) {
        cnt[c]++;
    }

    bool check (int c) {
        return cnt[c] == 0;
    }
};

int n, m, cnt;

vector<int> GM[MAXN];

struct Node {
    int par;
    bool y1, y2;
} nodes[MAXN];

vector<int> xSet, ySet;

int que[MAXN];

int BFS () {
    int ft = 0, bk = 0;
    REP (i, cnt) {
        if (nodes[i].y1) {
            nodes[i].par = i;
            que[bk++] = i;
        }
    }

    while (ft < bk) {
        int cur = que[ft++];

        if (nodes[cur].y2) {
            return cur;
        }

        for (auto v : GM[cur]) {
            if (nodes[v].par == -1) {
                nodes[v].par = cur;
                que[bk++] = v;
            }
        }
    }

    return -1;
}

void BuildGraph () {
    REP (i, MAXN) {
        GM[i].clear();
    }
    for (auto u : xSet) {
        MatroidZVector zm;
        MatroidColor zc;

        for (auto v : xSet) {
            if (u != v) {
                zm.insert(element[v].zvec);
                zc.insert(element[v].color);
            }
        }


        for (auto v : ySet) {
            if (zm.check(element[v].zvec)) {
                GM[u].eb(v);
            }
            if (zc.check(element[v].color)) {
                GM[v].eb(u);
            }
        }
    }

}

void BuildTag () {
    MatroidZVector zm;
    MatroidColor zc;
    for (auto el : xSet) {
        zm.insert(element[el].zvec);
        zc.insert(element[el].color);

        nodes[el].y1 = false;
        nodes[el].y2 = false;
        nodes[el].par = -1;
    }

    for (auto el : ySet) {
        nodes[el].y1 = zm.check(element[el].zvec);
        nodes[el].y2 = zc.check(element[el].color);
        nodes[el].par = -1;
    }
}

vector<ll> MatroidInetersection () {

    while (true) {
        xSet.clear();
        ySet.clear();

        REP (i, cnt) {
            if (element[i].inSet) {
                xSet.eb(i);
            } else {
                ySet.eb(i);
            }
        }
//        debug(xSet);
//        debug(ySet);

        BuildGraph();
        BuildTag();

        int nw = -1;
        for (auto el : ySet) {
            if (nodes[el].y1 && nodes[el].y2) {
                nw = el;
                break;
            }
        }

        if (nw != -1) {
            element[nw].inSet = true;
            continue;
        }

        int ed = BFS();
        if (ed == -1) {
            break;
        } else {
            vector<int> path;
            while (!nodes[ed].y1) {
                path.eb(ed);
                ed = nodes[ed].par;
            }
            path.eb(ed);

            debug(path);
            assert(SZ(path) & 1);
            debug(xSet, ySet);
            for (int i=0; i<SZ(path); i++) {
                debug(ed, i, element[path[i]].inSet);
                assert(element[path[i]].inSet ^ (i&1) ^ 1);
                element[path[i]].inSet ^= 1;
            }
        }
    }

    vector<ll> res;
    for (int i=n; i<cnt; i++) {
        if (element[i].inSet) {
            res.emplace_back(element[i].zvec);
        }
    }

    for (int i=0; i<n; i++) {
        if (!element[i].inSet) {
            cout << -1 << endl;
            exit(0);
        }
    }
    return res;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;
    REP (i, n) {
        element[i] = {i, 0, false};
        cin >> element[i].zvec;
    }

    cnt = n;
    cin >> m;
    REP (i, m) {
        int k;
        cin >> k;

        REP (j, k) {
            ll d;
            cin >> d;
            element[cnt++] = {n+i, d, false};
        }
    }

    auto ans = MatroidInetersection();

    if (SZ(ans) == m) {
        for (auto el : ans) {
            cout << el << endl;
        }
    } else {
        cout << -1 << endl;
    }

}
