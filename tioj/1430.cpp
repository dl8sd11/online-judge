#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> pii;
#define SZ(i) int(i.size())

int n, k, m;

vector<int> cand;
vector<pii> no, yes;

vector<int> L, R, lstL, lstR, sumL, sumR;

int main () {
    cin.tie(0);
    ios_base::sync_with_stdio(0);

    cin >> n >> k >> m;
    for (int i=0; i<m; i++) {
        int l, r, w;
        cin >> l >> r >> w;
        if (w) {
            yes.emplace_back(l, r);
        } else {
            no.emplace_back(l, r);
        }
    }    
    sort(no.begin(), no.end());

    for (int i=1, idx=0, ban=-1; i<=n; i++) {
        while (idx < SZ(no) && no[idx].first == i) {
            ban = max(ban, no[idx++].second);
        }
        if (ban < i) {
            cand.emplace_back(i);
        }
    }

#ifdef tmd
    for (auto v : cand) cout << v << " ";
    cout << endl;
#endif

    int sz = cand.size();
    L.resize(cand.size(), sz);
    R.resize(cand.size(), -1);
    lstL.resize(sz);
    lstR.resize(sz);
    sumL.resize(sz);
    sumR.resize(sz);

    vector<int> ans;
    for (auto v : yes) {
        int l = lower_bound(cand.begin(), cand.end(), v.first)-cand.begin();
        int r = upper_bound(cand.begin(), cand.end(), v.second)-cand.begin()-1;

        L[l] = min(L[l], r);
        R[r] = max(R[r], l);
    }

    for (int i=0, lst=-1, sum=0; i<sz; i++) {
        if (R[i] > lst) {
            lst = i;
            sum++;
        }     
        lstR[i] = lst;
        sumR[i] = sum;
    }

    for (int i=sz-1, lst=sz, sum=0; i>=0; i--) {
        if (L[i] < lst) {
            lst = i;
            sum++;
        }
        lstL[i] = lst;
        sumL[i] = sum;
    }

    assert(sz >= k);
    if (sz == k) {
        for (auto v : cand) {
            ans.emplace_back(v);
        }
    } else {
        if (L[0] == 0) {
            ans.emplace_back(cand[0]);
        }
        if (R[sz-1] == sz-1) {
            ans.emplace_back(cand[sz-1]);
        }
        for (int i=1; i<sz-1; i++) {
            int sum = sumR[i-1];
            int lst = lstR[i-1];
            if (R[i] > lstR[i-1]) {
                sum++;
                lst = i-1;
            }

            sum += sumL[lst+1];
            if (sum > k || L[i] == i) {
                ans.emplace_back(cand[i]);
            }
        }
    }

    sort(ans.begin(), ans.end());
    ans.resize(unique(ans.begin(), ans.end())-ans.begin());

    if (ans.empty()) {
        cout << -1 << endl;
    } else {
        for (auto v : ans) {
            cout << v << '\n';
        }
    }
}
