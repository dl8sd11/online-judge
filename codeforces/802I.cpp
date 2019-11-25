#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;

struct SuffixArray {
    string s;
    int n;
    vector<int> sa, rk, lcp, t;

    SuffixArray (const string &str) : s(str), n(SZ(str)), sa(n), rk(n), lcp(n), t(n) {
        buildSaRk();
        buildLcp();
    }


    void buildSaRk () {
        REP (i, n) {
            sa[i] = i;
            rk[i] = s[i];
        }
        if (n == 1) {
            rk[0] = 0;
        }
        for (int h=1; t[n-1] != n-1; h <<= 1) {
            auto cmp = [&] (int i, int j) {
                if (rk[i] != rk[j]) {
                    return rk[i] < rk[j];
                } else {
                    if (i+h<n && j+h<n) {
                        return rk[i+h] < rk[j+h];
                    } else {
                        return i > j;
                    }
                }
            };
            sort(sa.begin(), sa.end(), cmp);

            REP1 (i, n-1) {
                t[i] = t[i-1] + cmp(sa[i-1], sa[i]);
            }
            REP (i, n) {
                rk[sa[i]] = t[i];
            }
        }
    }

    void buildLcp () {
        int len = 0;
        REP (i, n) {
            if (rk[i] == 0) {
                len = 0;
            } else {
                len = max(len - 1, 0);
                int p = sa[rk[i] - 1];
                while (p+len<n && i+len<n && s[p+len] == s[i+len]) {
                    len++;
                }
            }
            lcp[rk[i]] = len;
        }
    }
};

ll cnt[MAXN];
int djs[MAXN], sz[MAXN];

int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

void mrg (int x, int y, int len) {
    x = fnd(x), y = fnd(y);
    if (sz[x] > sz[y]) {
        swap(x, y);
    }
    djs[x] = y;

    cnt[sz[x]] -= len;
    cnt[sz[y]] -= len;
    sz[y] += sz[x];
    cnt[sz[y]] += len;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    int t;
    cin >> t;
    while (t--) {
        memset(cnt, 0, sizeof(cnt));

        string str;
        cin >> str;
        int n = SZ(str);
        SuffixArray sa(str);
#ifdef tmd
        REP (i, n) {
            cout << sa.sa[i] << " ";
        }cout << endl;
        REP (i, n) {
            cout << sa.lcp[i] << " ";
        }cout << endl;
#endif

        vector<pair<int,int> > vp;
        for (int i=1; i<n; i++) {
            vp.emplace_back(sa.lcp[i], i-1);
        }
        sort(vp.rbegin(), vp.rend());

        cnt[1] += ll(n+1) * n / 2;
        REP (i, MAXN) {
            sz[i] = 1;
            djs[i] = i;
        }

        for (auto p : vp) {
            mrg(p.second, p.second+1, p.first);
        }

        ll ans = 0;
        REP (i, MAXN) {
            ans += 1LL * i * i * cnt[i];
            assert(cnt[i] >= 0);
        }
        cout << ans << endl;
    }
}
/*
4
aa
abcd
ccc
abcc

*/
