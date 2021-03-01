#include "lib1956.h"
#include <bits/stdc++.h>
#define SZ(i) int(i.size())
#define REP(i,n) for(int i=0;i<n;i++)
using namespace std;
typedef pair<int,int> pii;
typedef long long ll;

int solve (int l, int u, int* w, int w_len, int* re) {

    vector<pii> vec;
    REP (i, w_len {
        vec.emplace_back(w[i], i);
    }
    sort(vec.begin(),vec.end());


    int R = 0;
    ll sum = 0;
    for (int L=0;L<SZ(vec);L++) {
        R = max(L, R);
        while (R<SZ(vec) && sum+vec[R].first<l) {
            sum += vec[R].first;
            R++;
        }

        if (R<SZ(vec) && sum+vec[R].first<=u) {
            for (int i=L;i<=R;i++) {
                re[i] = (vec[i].second);
            }
            return R-L+1;
        }

        sum -= vec[L].first;
        sum = max(0LL, sum);
    }

    return 0;
}
