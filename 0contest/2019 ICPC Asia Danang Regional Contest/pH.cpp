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
template<typename T> ostream &operator << (ostream &os,array<T,6> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 11;
const ll MOD = 1000000007;

int r, c, ans;
array<int,6> state[MAXN];
array<int,6> tc[MAXN], tr[MAXN];

bool valid (const array<int,6> &a, const array<int,6> &gen) {
    array<int,6> pd = {};

    int cnt = 0, sz = 0;
    REP (i, SZ(a)+1) {
        if (i==SZ(a) || a[i] == 0) {
            if (cnt) {
                pd[sz++] = (cnt);
            }
            cnt = 0;
        } else {
            cnt++;
        }
    }

    return pd == gen;
}

vector<array<int,6> > vst[MAXN];
void dfs (int id) {
    if (id == r) {
        bool ps = true;
        REP (i, c) {
            array<int,6> cur = {};
            int sz = 0;
            REP (j, r) {
                cur[sz++] = (state[j][i]);
            }

            if (!valid(cur, tc[i])) {
                ps = false;
                break;
            }
        }

        if (ps) {
//            debug(state);
            ans++;
        }
    } else {
        for (auto s : vst[id]) {
            state[id] = (s);
            dfs(id+1);
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> r >> c;

    REP (i, r) {
        int sz;
        cin >> sz;
        REP (j, sz) {
            int x;
            cin >> x;
            tr[i][j] = (x);
        }
    }

    REP (i, c) {
        int sz;
        cin >> sz;
        REP (j, sz) {
            int x;
            cin >> x;
            tc[i][j] = (x);
        }
    }

    REP (i, 1<<c) {
        array<int,6> cur = {};

        int sz = 0;
        REP (j, c) {
            cur[sz++] = ((i>>j) & 1);
        }

        REP (id, r) {
            if (valid(cur, tr[id])) {
                vst[id].eb(cur);
            }
        }
    }

    debug(vst[0].size());
    debug(vst[0]);
    debug(vst[1]);
    debug(vst[2]);

    dfs(0);

    cout << ans << endl;
}
/*
3 2
1 2
0
1 1
1 1
2 1 1
*/
