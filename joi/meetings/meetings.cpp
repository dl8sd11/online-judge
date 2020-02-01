#include "meetings.h"
#include <bits/stdc++.h>
using namespace std;
#define SZ(i) int(i.size())


struct Subtree {
    int rt;
    vector<int> nd;
};

void solve (vector<int> node) {
    int rt = node[0];

    vector<Subtree> sub;
    for (int i=1;i<SZ(node);i++) {
        bool flag = false;
        for (auto &tr : sub) {
            int ret = Query(tr.rt, node[i], rt);
            if (ret != rt) {
                if (ret == node[i]) {
                   tr.rt =  node[i];
                }
                tr.nd.emplace_back(node[i]);
                flag = true;
                break;
            }
        }
        if (!flag) {
            sub.push_back({node[i],{node[i]}});
        }
    }

    for (auto &tr : sub) {
        if (rt < tr.rt) {
            Bridge(rt, tr.rt);
        } else {
            Bridge(tr.rt, rt);
        }
        solve(tr.nd);
    }
}

void Solve(int N) {
    vector<int> node;
    for (int i=0;i<N;i++) {
        node.emplace_back(i);
    }

    srand(279936);
    random_shuffle(node.begin(),node.end());
    solve(node);

}
