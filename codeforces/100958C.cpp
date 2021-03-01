#include <bits/stdc++.h>
typedef long long ll;
using namespace std;

ll n;
ll mask[11], a[11];
ll ans = 0x3f3f3f3f3f3f3f3f;

void dfs (int idx, ll *b) {
    if (idx == n) {
        ll cur = 0;
        ll tot = 0;
        for (int i=0; i<5; i++) {
            tot |= mask[i];
            cur += b[i] - __builtin_popcount(mask[i]);
        }
        cur += __builtin_popcount(tot);
        ans = min(ans, cur);
    } else {
        for (int i=0; i<(1<<10); i++) {
            mask[idx] = i;
            bool flag = true;
            for (int j=0; j<idx; j++) {
                if (__builtin_popcount(mask[idx]&mask[j]) >= 2) {
                    flag = false;
                }
            }
            if (flag && __builtin_popcount(i) <= b[idx]) {
                dfs(idx+1, b);
            }
        }
    }
}

void solve (ll *b) {
    mask[0] = 3;
    mask[1] = 5;
    mask[2] = 6;

    int cnt = 3;
    for (int i=0; i<3; i++) {
        for (int j=0; j<min(2LL,b[i]-2); j++) {
            mask[i] += 1LL<<cnt;
            cnt++;
        }
    }
    dfs(3, b);
}

ll x[11];
int main () {
    cin >> n;
    for (int i=0; i<n; i++) {
        cin >> a[i];
    }
    if (n == 1) {
        cout << a[0] << endl;
    } else if (n == 2) {
        cout << a[0] + a[1] - 1 << endl;
    } else {
        vector<int> perm;
        for (int i=0; i<n; i++) {
            perm.emplace_back(i);
        }
        set<set<int> > dup;
        do {
            set<int> f3;
            for (int i=0; i<3; i++) {
                f3.insert(perm[i]);
            }

            if (dup.count(f3) == 0) {
                dup.insert(f3);
                for (int j=0; j<n; j++) {
                    x[j] = a[perm[j]];
                }
                solve(x);
            }
           

        } while (next_permutation(perm.begin(), perm.end()));
        cout << ans << endl;

    }
}
