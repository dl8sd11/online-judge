#include <bits/stdc++.h>
using namespace std;
#define endl '\n'
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)

int greedy (vector<int> &v) {
    int fnd = -1;
    for (int i=int(v.size()-2);i>=0;i--) {
        if (v.back() % v[i] != 0) {
           fnd = v[i];
           break; 
        }
    }

    if (fnd == -1) {
        return v.back();
    }

    for (int i=int(v.size()-2); i>=0; i--) {
        if (v.back() % v[i] != 0 && fnd % v[i] != 0) {
            return v.back() + v[i] + fnd; 
        }
    }

    return v.back() + fnd;
}

int counter(vector<int> &v) {
    if (v.back() % 2 != 0 || v.back() % 3 != 0 || v.back() % 5 != 0) {
        return -1e8;
    }

    if (find(v.begin(), v.end(), v.back() / 2) == v.end()) {
        return -1e8;                 
    }

    if (find(v.begin(), v.end(), v.back() / 3) == v.end()) {
        return -1e8;                 
    }
    
    if (find(v.begin(), v.end(), v.back() / 5) == v.end()) {
        return -1e8;                 
    }

    return v.back() / 2 + v.back() / 3 + v.back() / 5;
}
int main () {
    IOS();

    int q, n;
    cin >> q;
    while (q--) {
        cin >> n;
        vector<int> v;
        for (int i=0;i<n;i++) {
            int d;
            cin >> d;
            v.emplace_back(d);
        }
        
        sort(v.begin(), v.end());
        int res = greedy(v);
        res = max(res, counter(v));

        cout << res << endl;
    }
}
