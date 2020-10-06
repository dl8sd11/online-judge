#include <bits/stdc++.h>
#include "prize.h"
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define SZ(i) int(i.size())
#define ALL(i) i.begin(), i.end()
#define MEM(i,a) memset(i, (a), sizeof(i))
#define X first
#define Y second
#define eb emplace_back
#define pb push_back
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d-(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do (T &&x) {cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {cerr<<x<<", ";_do(y...);}
#else
#define debug(...)
#endif


map<int, vector<int> > mem;
vector<int> sask (int idx) {
    if (mem.count(idx) == 0) {
        mem[idx] = ask(idx);
    }
    return mem[idx];
}

int find_best(int n) {

    srand(880301);
    int mx = 0;
    for (int i=0; i<50; i++) {
        vector<int> res = sask(rand() % n);
        mx = max(mx, res[0] + res[1]);
    }
    debug(mx);

    int sp = rand() % n;
	for(int i = sp; i < n; i++) {
		std::vector<int> res = sask(i);
		if(res[0] + res[1] == 0) return i;
        if (res[0] + res[1] < mx) continue;
        int L = i, R = n;
        while (L < R - 1) {
            int M = (L + R) >> 1;
            vector<int> resM = sask(M);
            if (resM[0] + resM[1] == 0) return M;
            if (resM == res) {
                L = M;
            } else {
                R = M;
            }
        }
        debug(i, R);
        i = R - 1;
	}
	for(int i = 0; i < sp; i++) {
		std::vector<int> res = sask(i);
		if(res[0] + res[1] == 0) return i;
        if (res[0] + res[1] < mx) continue;
        int L = i, R = sp;
        while (L < R - 1) {
            int M = (L + R) >> 1;
            vector<int> resM = sask(M);
            if (resM[0] + resM[1] == 0) return M;
            if (resM == res) {
                L = M;
            } else {
                R = M;
            }
        }
        debug(i, R);
        i = R - 1;
	}
	return 0;
}
