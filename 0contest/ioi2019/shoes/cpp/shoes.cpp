#include "shoes.h"
#include <bits/stdc++.h>

using namespace std;
typedef long long ll;

#ifdef tmd
#define debug(...) fprintf(stderr,"%d (%s) = ",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do (T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do (T &&x, S &&...y) {cerr<<x<<",";_do(y...);}
template<typename IT> ostream &printRng (IT bg, IT ed, ostream &os) {
    os<<"{";
    for (IT it=bg; it!=ed; it++) {
        if (it!=bg) {
            os<<",";
        }
        os<<(*it);
    }
    return os<<"}";
}
template<typename T> ostream &operator << (ostream &os, vector<T> &vec) {
    return printRng(vec.begin(), vec.end(), os);
}
#else
#define debug(...)
#endif // tmd

const int MAXN = 200005;
queue<int> idx[MAXN][2];

int bit[MAXN];

void add (int x, int y) {
    for (;x<MAXN;x+=-x&x) {
        bit[x] += y;
    }
}

int qry (int x) {
    int ret = 0;
    for (;x>0; x-=-x&x) {
        ret += bit[x];
    }
    return ret;
}

ll inv (const vector<int> &vec) {
    ll res = 0;
    for (auto it=vec.rbegin();it!=vec.rend();it++) {
        int v = *it;
        res += qry(v);
        add(v, 1);
    }
    return res;
}

long long count_swaps(std::vector<int> s) {
    vector<int> ser(s.size());
    int cnt = 1;
    for (int i=0; i<int(s.size()); i++) {
        const int v = s[i];

        if (idx[abs(v)][v>0].empty()) {
            ser[i] = v > 0 ? cnt + 1 : cnt;
            idx[abs(v)][v<0].emplace(v>0?cnt:cnt+1);
            cnt+=2;
        } else {
            ser[i] = idx[abs(v)][v>0].front();
            idx[abs(v)][v>0].pop();
        }
    }
    debug(ser);
	return inv(ser);
}
