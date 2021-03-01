#include <bits/stdc++.h>
using namespace std;
using pvec = vector<pair<int,int> >;
using ll = long long;

struct Trans {
    int i, l, r;
};
ostream &operator << (ostream &_s, const Trans& tr) {
    return _s << "{"  << tr.i << "," << tr.l << "," << tr.r << "}";
}

pvec orderLow (pvec vec) {
    pvec res;
    sort(vec.begin(), vec.end());
    for (auto p : vec) {
        if (res.empty() || p.second < res.back().second) {
            res.push_back(p);
        }
    }
    return res;
}

pvec orderHigh (pvec vec) {
    pvec res;
    sort(vec.begin(), vec.end());
    for (auto p : vec) {
        while (res.size() && res.back().second <= p.second) {
            res.pop_back();
        }
        res.push_back(p);
    }
    return res;
}
ll solve (pvec plo, pvec phi) {
    ll mans = 0;
    auto f = [&](int i, int j) {
        assert(i < plo.size());
        assert(j < phi.size());
        return (plo[i].first >= phi[j].first || plo[i].second >= phi[j].second) ?
            0 : (ll(plo[i].first - phi[j].first) * (plo[i].second - phi[j].second));
    };
    int m = int(plo.size()), n = int(phi.size());
    sort(plo.begin(), plo.end());
    sort(phi.begin(), phi.end());
    plo = orderLow(plo);
    phi = orderHigh(phi);
    m = int(plo.size()), n = int(phi.size());

    deque<Trans> deq;


    int R = 0;
    for (int i=0; i<m; i++) {
        while (R < n && phi[R].second > plo[i].second) {
            R++;
        }
        while (!deq.empty() && \
             f(deq.back().i, deq.back().l) < f(i, deq.back().l)) {
            deq.pop_back();
        }
        if (!deq.empty()) {
            int l = deq.back().l, r = deq.back().r;
            while (l < r - 1) {
                int mid = (l + r) >> 1;
                if (f(deq.back().i, mid) < f(i, mid)) {
                    r = mid;
                } else {
                    l = mid;
                }
            }
            deq.back().r = r;
            if (r != R) deq.push_back({i, r, R});
        } else {
            deq.push_back({i, 0, R});
        }
    }

    vector<ll> mx;
    for (int i=0; i<n; i++) {
        while (deq.size() && deq.front().r <= i) {
            deq.pop_front();
        }
        if (deq.size()) {
            mx.push_back(f(deq.front().i, i));
        }
    }

    ll ans = mx.empty() ? 0LL : *max_element(mx.begin(), mx.end());

    return ans;
}

int main () {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    int m, n;
    cin >> m >> n;
    vector<pair<int,int> > plo(m), phi(n);

    for (int i=0; i<m; i++) {
        cin >> plo[i].first >> plo[i].second;
    }
    for (int i=0; i<n; i++) {
        cin >> phi[i].first >> phi[i].second;
    }

    cout << solve(plo, phi) << endl;
}

