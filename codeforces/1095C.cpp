#include <bits/stdc++.h>
using namespace std;

int n,k;
vector<int> ans;
priority_queue<int> pq;
int main () {
    cin >> n >> k;
    for (int i=1;i<=(1e9);i<<=1) {
        if (i & n) {
            pq.emplace(i);
        }
    }

    
    while (pq.size() < k) {
        int cur = pq.top();
        pq.pop();
        if (cur == 1) {
            break;
        } else {
            pq.emplace(cur/2);
            pq.emplace(cur/2);
        }
    }
    

    if (pq.size() != k) {
        cout << "NO" << endl;
    } else {
        cout << "YES" << endl;
        while (pq.size()) {
            cout << pq.top();
            pq.pop();
            cout << (pq.size() == 0 ? '\n' : ' ');
        }
    }
}