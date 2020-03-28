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

void zero () {
    cout << 0 << endl;
    exit(0);
}

const int MAXN = 1003;
const ll MOD = 1000000007;

int n, cnt[MAXN], mx;
vector<int> cur;
vector<vector<int> > ans;

void dfs (int idx, int lst) {
    if (idx == n) {
        ans.eb(cur);
        sort(ALL(ans.back()));
        return;
    }

    while (cnt[lst] == 0) {
        lst--;
    }

    if (cnt[lst] == 2) {
        bool valid = true;
        cur.eb(lst);
        cur.eb(mx - lst);

        REP (i, idx) {
            if (--cnt[abs(cur[i]-cur[idx])] < 0) {
                valid = false;
            }
        }

        REP (i, idx+1) {
            if (--cnt[abs(cur[i]-cur[idx+1])] < 0) {
                valid = false;
            }
        }

        if (valid) {
            dfs(idx+2, lst);
        }

        REP (i, idx) {
            ++cnt[abs(cur[i]-cur[idx])];
        }

        REP (i, idx+1) {
            ++cnt[abs(cur[i]-cur[idx+1])];
        }

        cur.pop_back();
        cur.pop_back();
    } else if (cnt[lst] == 1) {
        REP (hd, 2) {
            bool valid = true;
            cur.eb(hd ? lst : mx - lst);

            REP (i, idx) {
                if (--cnt[abs(cur[i]-cur[idx])] < 0) {
                    valid = false;
                }
            }

            if (valid) {
                dfs(idx+1, lst);
            }

            REP (i, idx) {
                ++cnt[abs(cur[i]-cur[idx])];
            }

            cur.pop_back();
        }
    }
}

/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

    REP (i, n * (n-1) / 2) {
        ll x;
        cin >> x;
        if (x >= 1000) {
            zero();
        }
        mx = max(mx, int(x));
        cnt[mx]++;
    }

    if (cnt[mx] > 1) {
        zero();
    }

    cur.eb(0);
    cur.eb(mx);
    cnt[mx]--;

    dfs(2, mx);

    sort(ALL(ans));
    cout << ans.size() << endl;
    for (auto v : ans) {
        REP (i, n) {
            cout << v[i] << " \n"[i==n-1];
        }
    }
}
