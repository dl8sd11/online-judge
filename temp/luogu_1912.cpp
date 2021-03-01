#include <bits/stdc++.h>
using namespace std;
using ld = long double;
using ll = long long;
using vs = vector<string>;
#define endl '\n'

ld mpow (ld base, int ep) {
    ld res = 1;
    while (ep) {
        if (ep & 1) res = res * base;
        base = base * base;
        ep >>= 1;
    }
    return res;
}

struct DP {
    struct Seg {
        int i, l, r;
    };
    int l, p, n;
    vector<ld> dp;
    vector<int> from, pre;

    ld cost (int i, int j) { // dp[j] + (i-j-1+s[i]-s[j]-l)^p
        return dp[j] + mpow(abs(i-j-1+pre[i]-pre[j]-l), p);
    }

    int bs (int x, int y, int L, int R) { // search when y overtakes x
        while (L < R - 1) {
            int M = (L + R) >> 1;
            if (cost(M, x) > cost(M, y)) R = M;
            else L = M;
        }
        return R;
    }

    DP (const vs &lines, int _l, int _p) : l(_l), p(_p), n(int(lines.size())) {
        pre.resize(n + 1, 0);
        dp.resize(n + 1, 0);
        from.resize(n + 1, 0);
        for (int i=1; i<=n; i++) {
            pre[i] = pre[i-1] + int(lines[i-1].size());
        }

        deque<Seg> deq;
        deq.push_back({0, 0, n+1});

        for (int i=1; i<=n; i++) {
            while (deq.size() && deq.front().r <= i) deq.pop_front();
            assert(deq.size());
            from[i] = deq.front().i;
            dp[i] = cost(i, from[i]);

            while (deq.size() && cost(deq.back().l, deq.back().i) > cost(deq.back().l, i)) {
                deq.pop_back();
            }
            if (deq.empty()) {
                deq.push_back({i, 0, n+1});
            } else {
                int over = bs(deq.back().i, i, deq.back().l, deq.back().r);
                deq.back().r = over;
                if (over != n+1) deq.push_back({i, over, n+1});
            }
        }
    }
};

void output (vs &res, const DP &dp, int n, const vs &lines) {
    int ptr = n;
    while (ptr != 0) {
        string cur;
        for (int i=dp.from[ptr]+1; i<=ptr; i++) {
            cur += lines[i-1];
            if (i != ptr) cur += " ";
        }
        ptr = dp.from[ptr];
        res.emplace_back(cur);
    }
    reverse(res.begin(), res.end());
}

void solve () {
    vs lines;
    int n, l, p;
    cin >> n >> l >> p;
    for (int i=0; i<n; i++) {
        string str;
        cin >> str;
        lines.emplace_back(str);
    }

    DP dp(lines, l, p);
    if (dp.dp[n] > 1e18) {
        cout << "Too hard to arrange" << endl;
    } else {
        cout << ll(dp.dp[n]) << endl;
        vs res;
        output(res, dp, n, lines);
        for (string &s : res) {
            cout << s << endl;
        }
    }

    cout << "--------------------" << endl;

}
int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int t;
    cin >> t;
    while (t--) {
        solve();
    }
}
