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


const int MAXN = 1000005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, c[MAXN];
int sel[MAXN], cnt[MAXN];

inline int nxt (int x) {
    return (x==n-1?0:x+1);
}

inline int prv (int x) {
    return (x==0?n-1:x-1);
}

bool inq[MAXN];

inline void add (queue<int> &que, int &x) {
    if (!inq[x]) {
        inq[x] = true;
        que.emplace(x);
    }
}

bool check (int x) {
    cnt[sel[x]]--;

    int nx = nxt(x);
    int l = c[x]*(cnt[nx]+1);
    int r = c[nx]*(cnt[x]+1);

    cnt[sel[x]]++;

    if (l == r) {
        return false;
    } else {
        return sel[x] == x ? r>l : l>r;
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

    #ifdef tmd
    n = rng() % 100;
    cout << n << endl;
    #else
    cin >> n;
    #endif // tmd
    REP (i, n) {
        #ifdef tmd
        c[i] = rng() % 10 + 1;
        cout << c[i] << " \n"[i==n-1];
        #else
        cin >> c[i];
        #endif // tmd
    }
    REP (i, n) {
        if (c[nxt(i)] > c[i]) {
            sel[i] = nxt(i);
            cnt[nxt(i)]++;
        } else {
            sel[i] = i;
            cnt[i]++;
        }
    }

    queue<int> bfs;
    REP (i, n) {
        if (check(i)) {
            add(bfs, i);
        }
    }

    int upd = 0;

    int lim = max(1000,n) * __lg(max(1000,n));
    while (bfs.size()) {
        int cur = bfs.front();
        upd++;
        if (upd > lim) {
            break;
        }
        debug(upd);

        bfs.pop();

        if (check(cur)) {
            int nc = nxt(cur), pc = prv(cur);

            if (sel[cur] == cur) {
                sel[cur] = nc;
                cnt[nc]++;
                cnt[cur]--;
            } else {
                sel[cur] = cur;
                cnt[nc]--;
                cnt[cur]++;
            }

            if (check(nc)) {
                add(bfs, nc);
            }
            if (check(pc)) {
                add(bfs, pc);
            }
        }
    }

    if (bfs.empty()) {
        REP (i, n) {
            cout << sel[i]+1 << " \n"[i==n-1];
        }
    } else {
        cout << "NIE" << endl;
    }
}
