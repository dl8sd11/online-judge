#include <bits/stdc++.h>
using namespace std;


/********** Good Luck :) **********/
int main () {
    string s;
    int k;
    cin >> s >> k;

    int n = int(s.size());
    vector<pair<char, int>> gp;
    int l[100005] = {};
    int r[100005] = {};
    int cnt = 1;

    queue<int> bfs;
    for (int i=1; i<=n; i++) {
        if (i == n || s[i] != s[i-1]) {
            l[gp.size()] = gp.size() - 1;
            r[gp.size()] = gp.size() + 1;
            if (cnt >= k) {
                bfs.emplace(gp.size());
            }
            gp.emplace_back(s[i-1], cnt);
            cnt = 0;
        }
        cnt++;
    }
    int N = gp.size();

    bool vis[100005] = {};
    while (bfs.size()) {
        int cur = bfs.front();
        bfs.pop();
        if (vis[cur]) {
            continue;
        }
        gp[cur].second %= k;
        

        if (gp[cur].second == 0) {
            int rcur = r[cur];
            int lcur = l[cur];
            if (rcur != N) {
                l[rcur] = lcur;
            }
            if (lcur != -1) {
                r[lcur] = rcur;
            }
            
            if (lcur != -1 && rcur != N) {
                if (gp[lcur].first == gp[rcur].first) {
                    r[lcur] = r[rcur];
                    if (r[rcur] != N) {
                        l[r[rcur]] = lcur;
                    }
                    gp[lcur].second += gp[rcur].second;
                    gp[rcur].second = 0;
                    if (gp[lcur].second >= k) {
                        bfs.emplace(lcur);
                    }
                }
            }
        }
    }

    string ret;
    for (auto p : gp) {
        for (int i=0; i<p.second; i++) {
            ret += p.first;
        }
    }

    cout << ret << endl;

    return 0;
}
