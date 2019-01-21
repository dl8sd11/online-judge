#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300003;
int n,len;
vector<int> edge[MAXN];
int dep[MAXN];

int fnd_odd (int nd) {
    int ret;
    if (edge[nd].size() == 0) {
        return -1;
    } else if (edge[nd].size() == 1) {
        ret = fnd_odd(edge[nd].front());
        if (ret == -1) {
            return nd;
        } else {
            return ret;
        }
    } else {
        ret = fnd_odd(edge[nd].front());
        if (ret == -1) {
            return fnd_odd(edge[nd].back());
        } else {
            return ret;
        }
    }
}
bool add_leaf(int level) {

}

int main () {
    cin >> n;

    cin >> len;
    for (int i=1;i<len;i++) {
        edge[i].emplace_back(i+1);
    }

    for (int i=1;i<n;i++) {
        cin >> len;
        if (!add_leaf(len)) {
            cout << "NIE" << endl;
            return 0;
        }
    }
}