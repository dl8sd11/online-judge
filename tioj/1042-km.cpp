#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int> > wei;

vector<int> x_vis, y_vis, lx, ly, y_match;

bool dfs (int x) {
    if (x_vis[x]) return false;
    x_vis[x] = true;

    for (int y=0; y<n; y++) {
        if (lx[x] + ly[y] == wei[x][y]) {
            y_vis[y] = true;
            if (y_match[y] == -1 || dfs(y_match[y])) {
                y_match[y] = x;
                return true;
            }
        }
    }
    return false;
}

void relabel () {
    int d = INT_MAX;
    for (int x=0; x<n; x++) {
        for (int y=0; y<n; y++) {
            if (x_vis[x] == true && y_vis[y] == false) {
                d = min(d, lx[x] + ly[y] - wei[x][y]);
            }
        }
    }

    for (int i=0; i<n; i++) {
        if (x_vis[i]) lx[i] -= d;
        if (y_vis[i]) ly[i] += d;
    }
}

int km () {
    y_match.clear();
    y_match.resize(n, -1);

    lx.clear();
    lx.resize(n, INT_MAX / 2);
    ly.clear();
    ly.resize(n, 0);

    x_vis.resize(n);
    y_vis.resize(n);

    for (int i=0; i<n; i++) {
        while (true) {
            fill(x_vis.begin(), x_vis.end(), 0);
            fill(y_vis.begin(), y_vis.end(), 0);
            if (dfs(i)) break;
            relabel();
        }
    }

    int sum = 0;
    for (int i=0; i<n; i++) sum += lx[i] + ly[i];
    return sum;
}
int main () {
    while (cin >> n && n != 0) {
        wei.clear();
        wei.resize(n, vector<int>(n, 0));
        for (int i=0; i<n; i++) {
            for (int j=0; j<n; j++) {
                int d;
                cin >> d;
                wei[i][j] = max(0, d);
            }
        }

        cout << km() << endl;
    }
}

