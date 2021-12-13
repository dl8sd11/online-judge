#include <bits/stdc++.h>
using namespace std;
using Edge = pair<int,int>;

vector<int> djs;

int fnd (int x) {
    return x == djs[x] ? x : djs[x] = fnd(djs[x]);
}

void mrg (int x, int y) {
    djs[fnd(x)] = fnd(y);
}

void conn (int x, int y) {
    mrg(x * 2, y * 2 + 1);
    mrg(x * 2 + 1, y * 2);
}

bool valid (int x, int y) {
    return !(fnd(x * 2) == fnd(y * 2));
}

void init (int n, vector<Edge> &edges) {
    djs.resize(n);
    iota(djs.begin(), djs.end(), 0);

    for (auto [x, y]: edges) {
        conn(x, y);
    }
}

int main() {
    int n, m;
    cin >> n >> m;
    vector<Edge> real;

    for (int i=0; i<m; i++) {
        int x, y;
        cin >> x >> y;
        real.emplace_back(x, y);
    }

    int p, k;
    cin >> p >> k;
    vector<vector<Edge> > unknown(p);
    for (int i=0; i<p; i++) {
        for (int j=0; j<k; j++) {
            int x, y;
            cin >> x >> y;
            unknown[i].emplace_back(x, y);
        }
    }

    int cnt = 0;
    while (true) {
        init(n * 2, real);

        int failAt = -1;
        for (int i=0; i<unknown.size(); i++) {
            for (auto [x, y] : unknown[i]) {
                bool v = valid(x, y);
                if (!v) {
                    failAt = i;
                    break;
                }
                conn(x, y);
            }

            if(failAt != -1) break;
        }

        if (failAt == -1) break;
        cout << failAt + 1 + cnt << endl;
        cnt++;

        unknown.erase(unknown.begin() + failAt);
    }
}
