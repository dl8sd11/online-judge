#pragma GCC optimize("Ofast,fast-math,unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx")
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;
typedef long long ll;


const int S = 1<<24; // buffer size
char buf[S], *p = buf, *q = buf;
inline char readchar() {
	if(p == q && (q = (p=buf)+fread(buf,1,S,stdin)) == buf) return EOF;
	return *p++;
}
inline void input(int& x) {
	x = 0;
	int c = readchar();
	while('0' > c || c > '9') c = readchar();
	while('0' <= c && c <= '9') x = (x*10) + (c^'0'), c = readchar();
}

struct SparseTable {
    int (*cmp) (int, int);
    vector<vector<int> > tbl;

    SparseTable (const vector<int> &a, int (*_cmp)(int, int)) {
        int N = int(a.size());
        int M = __lg(N) + 1;
        tbl.resize(M, vector<int>(N));
        tbl[0] = a;
        cmp = _cmp;

        for (int i=1; i<M; i++) {
            for (int j=0; j<N; j++) {
                if (j+(1<<i) <= N) {
                    tbl[i][j] = (*cmp)(tbl[i-1][j], tbl[i-1][j+(1<<i-1)]);
                }
            }
        }
    }

    int query (int l, int r) {
        int len = __lg(r-l);
        return cmp(tbl[len][l], tbl[len][r-(1<<len)]);
    }
};

int MN (int x, int y) {
    return x > y ? y : x;
}

int MX (int x, int y) {
    return x < y ? y : x;
}

inline int64_t gilbertOrder(int x, int y, int pow, int rotate) {
	if (pow == 0) {
		return 0;
	}
	int hpow = 1 << (pow-1);
	int seg = (x < hpow) ? (
		(y < hpow) ? 0 : 3
	) : (
		(y < hpow) ? 1 : 2
	);
	seg = (seg + rotate) & 3;
	const int rotateDelta[4] = {3, 0, 0, 1};
	int nx = x & (x ^ hpow), ny = y & (y ^ hpow);
	int nrot = (rotate + rotateDelta[seg]) & 3;
	int64_t subSquareSize = int64_t(1) << (2*pow - 2);
	int64_t ans = seg * subSquareSize;
	int64_t add = gilbertOrder(nx, ny, pow-1, nrot);
	ans += (seg == 1 || seg == 2) ? add : (subSquareSize - add - 1);
	return ans;
}

const int bsz = 1000;
struct Mo {
    int l, r, qid;
    int64_t ord;
    Mo (int L, int R, int Q) : l(L), r(R), qid(Q), ord(gilbertOrder(l, r, 21, 0)) {}
    bool operator < (const Mo &oth) const {
        return ord < oth.ord;
    }
};


int main () {

    int n, k;
    input(n);
    input(k);

    vector<int> h(n);
    for (int i=0; i<n; i++) {
        input(h[i]);
    }

    SparseTable smin(h, MN), smax(h, MX);
    vector<int> matchL(n), matchR(n);

    for (int l=0,r=0; r<n; r++) {
        while (smax.query(l,r+1) - smin.query(l,r+1) > k) {
            l++;
        }
        matchR[r] = l;
    }
    for (int l=0, r=0; l<n; l++) {
        r = max(r, l);
        while (r<n && smax.query(l,r+1) - smin.query(l,r+1) <= k) {
            r++;
        }
        matchL[l] = r - 1;
    }


    int q;
    input(q);
    vector<Mo> Mos;
    for (int i=0; i<q; i++) {
        int l, r;
        input(l);
        input(r);
        l--;
        Mos.emplace_back(l, r, i);
    }
    sort(Mos.begin(), Mos.end());

    ll cur = 0;
    int L = 0, R = 0;

    auto add = [&](int pos) {
        cur += min(R-L, 1+abs(pos - (pos == L ? matchL[L] : matchR[R-1])));
        return;
    };

    auto rmv = [&](int pos) {
        cur -= min(R-L, 1+abs(pos - (pos == L ? matchL[L] : matchR[R-1])));
        return;
    };

    vector<ll> ans(q);
    for (const Mo &itr : Mos) {
        int cL = itr.l;
        int cR = itr.r;

        while (cR > R) {
            R++;
            add(R-1);
        }
        while (cL < L) {
            L--;
            add(L);
        }
        while (cR < R) {
            rmv(R-1);
            R--;
        }
        while (cL > L) {
            rmv(L);
            L++;
        }

        ans[itr.qid] = cur;
    }

    for (ll x : ans) printf("%lld\n", x); 

}
