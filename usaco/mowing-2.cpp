#include <bits/stdc++.h>
using namespace std;

int dp[10][10];
int res[10];

const int inf = 1e6;
int main () {
    int n, t;
    cin >> n >> t;
    vector<pair<int,int> > pos(n);
    for (int i=0; i<n; i++) {
        cin >> pos[i].first >> pos[i].second;
    }
    pos.emplace_back(0, 0);
    sort(pos.begin(), pos.end());
    n++;

    for (int i=1; i<n; i++) {
        for (int j=0; j<i; j++) {
            if (pos[i].second > pos[j].second) {
                dp[i][j] = inf - (pos[i].first - pos[j].first)\
                           * (pos[i].second - pos[j].second) + res[j];
                res[i] = max(res[i], dp[i][j]);
            } 
        }
    }

    for (int i=1; i<n; i++) {
        for (int j=0; j<n; j++) {
            if (dp[i][j] == res[i]) {
                cout << "*";
            } else {
                cout << ".";
            }
        }
        cout << endl;

    }

    
}
