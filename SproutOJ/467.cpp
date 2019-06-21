#include <iostream>
#include <set>
#include <vector>
using namespace std;

const int MAXN = 2000006;

int n,k,q,b[MAXN],ans[MAXN];
vector<int> query[MAXN];

int main () {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }

    cin >> q;
    for (int qid = 0; qid < q; qid++) {
        int pos;
        cin >> pos;
        query[pos + k - 1].emplace_back(qid);
    }

    multiset<int> mn;
    for (int i = 0; i < n; i++) {
        mn.insert(b[i]);
        if (i >= k - 1) {
            int ret = *mn.begin();
            for (auto q : query[i]) {
                ans[q] = ret;
            }
            mn.erase(mn.find(b[i - k + 1]));
        }
    }

    for (int i = 0; i < q; i++) {
        cout << ans[i] << endl;
    }
}