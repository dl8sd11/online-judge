#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i, n) for(int i=1; i<=n; i++)
#define pb push_back
#define eb emlace_back
#define SZ(i) int(i.size())
#ifdef tmd
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#define IOS()
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#define endl '\n'
#define debug(...)
#endif

const int MAXN = 1000006;

string str, sub;

int cnt_dg (int val) {
    int cnt = 0;
    while (val) {
        val /= 10;
        cnt++;
    }
    return cnt;
}

typedef unsigned long long ull;
struct Hashing {
    ull pre[MAXN];
    ull b[MAXN];
    Hashing (ull bb, string &s) {
        b[0] = 1;
        REP1 (i, MAXN-1) {
            b[i] = b[i-1] * bb;
        }
        REP1 (i, SZ(s)) {
            pre[i] = pre[i-1] + ull(s[i-1]) * b[i-1];
        }
    }

    ull get (int l, int r, int shf) {
        return (pre[r+1] - pre[l]) * b[shf];
    }
};

int cnt[10];
int main () {
    IOS();

    cin >> str >> sub;
    int n = SZ(str);

    int sz = -1;
    REP1 (i, 8) {
        if (cnt_dg(n-i) == i) {
            sz = n-i;
            break;
        }
    }

    debug(sz);

    for (auto c : str) {
        cnt[c-'0']++;
    }

    int tsz = sz;
    while (tsz) {
        cnt[tsz%10]--;
        tsz /=10;
    }
    for (auto c : sub) {
        cnt[c-'0']--;
    }

    string ans;

    sort(fnl.begin(), fnl.end());
    if (sub.front() != '0') {
        ans = min(ans, sub + fnl);
    }

    int lc = 10;
    for (int i=9; i>=1; i--) {
        if (cnt[i]) {
            lc = i;
        }
    }
    debug(cnt[0], lc);


    string fnl;
    if (lc != 10) {
        fnl += '0' + lc;
        cnt[lc]--;
        REP (i, 10) {
            debug(i, cnt[i]);
            while (cnt[i]) {
                fnl += '0' + i;
                cnt[i]--;
            }
        }
    }
    debug(fnl, sub);

    if (SZ(fnl) == 0) {
        cout << sub << endl;
        return 0;
    }

    n = SZ(fnl);

    vector<Hashing> fsh, ssh;
    REP (i, 3) {
        int rnd = rand() % 10000 + 607;
        fsh.emplace_back(rnd, fnl);
        ssh.emplace_back(rnd, sub);
    }

    int pos = -1;
    REP1 (i, n) {
        if (i == n) {
            pos = i;
            break;
        }
        if (i == 0 && sub[0] == '0') {
            continue;
        }
        int L = 0, R = min(n-i, SZ(sub)) + 1;
        while (L < R - 1) {
            bool sm = true;
            int M = (L + R) >> 1;
            REP (j, SZ(fsh)) {
                if (fsh[j].get(i, i+M-1, 0) != ssh[j].get(0,M-1, i)) {
                    sm = false;
                }
            }
            if (sm) {
                L = M;
            } else {
                R = M;
            }
        }
        debug(L);
        if (L == n-i) {
            pos = i;
        } else if (L == SZ(sub) || fnl[i+L] > sub[L]) {
            pos = i;
            break;
        }

    }
    debug(pos);

    debug(pos);

    ans = max(ans,fnl.substr(0, pos) + sub + fnl.substr(pos));

    cout << ans << endl;
#ifdef tmd
    int l1, len;
    while (cin >> l1 >> len) {
        debug(fsh[0].get(l1, l1+len-1, 0));
        debug(ssh[0].get(0, len-1, l1));
    }
#endif
}
