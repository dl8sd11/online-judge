#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
#define first X
#define second Y
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define SZ(i) int(i.size())
#ifdef tmd
#define debug(...) fprintf(stderr,"#%d-(%s)=",__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do (T &&x) {cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y) {cerr<<x<<",";_do(y...);}
template<typename IT> ostream &__printRng (ostream& os, IT bg, IT ed) {
    for (IT it=bg; it!=ed; it++) {
        if (it == bg) os << "{" << *it;
        else os << "," << *it;
    }
    return os << "}";
}
template<typename T> ostream &operator << (ostream& os, const vector<T> &vec) {
    return __printRng(os,ALL(vec));
}
#else
#define debug(...)
#endif

#include "gondola.h"

int lvalid(int n, int inputSeq[])
{
    
    vector<int> sm;
    set<int> val;
    for (int i=0; i<n; i++) {
        if (inputSeq[i] <= n) {
            sm.push_back(inputSeq[i]);
        }
        val.insert(inputSeq[i]);
    }
    if (SZ(val) != n) return 0;
    int st = min_element(ALL(sm)) - sm.begin();
    for (int i=0; i<SZ(sm)-1; i++) {
        if (sm[(st+i)%SZ(sm)] >= sm[(st+i+1)%SZ(sm)]) {
            debug(i, st);
            return 0;
        }
    }

    return 1;
}

 
int valid(int n, int inputSeq[])
{
    
    vector<int> sm;
    set<int> val;
    for (int i=0; i<n; i++) {
        if (inputSeq[i] <= n) {
            sm.push_back(inputSeq[i]);
            val.insert(inputSeq[i]);
        }
    }
    if (SZ(val) != n) return 0;
    int st = min_element(ALL(sm)) - sm.begin();
    for (int i=0; i<SZ(sm)-1; i++) {
        if (inputSeq[(st+i)%SZ(sm)] >= inputSeq[(st+i+1)%SZ(sm)]) {
            return 0;
        }
    }
 
    return 1;
}
 
//----------------------

const int MAXN = 250005;
int replacement(int n, int gondolaSeq[], int rs[])
{
    set<int> alive;
    vector<int> fin, cur;

    int off = 1;
    for (int i=0; i<n; i++) {
        fin.eb(gondolaSeq[i]);
        if (fin.back() > n) alive.insert(i);
        else off = (n+fin.back()-i) % n;
    }
    debug(off);
    for (int i=0; i<n; i++) {
        cur.eb((off + i - 1) % n + 1);
    }
    debug(cur);
    int mx = *max_element(ALL(fin));
    vector<int> pos(mx+1, -1);
    for (int i=0; i<SZ(fin); i++) {
        pos[fin[i]] = i;
    }
    int res = 0;
    for (int i=n+1; i<=mx; i++) {
        if (pos[i] == -1) {
            int p = *alive.begin();
            rs[res++] = cur[p];
            cur[p] = i;
        } else {
            assert(alive.count(pos[i]));
            alive.erase(pos[i]);
            rs[res++] = cur[pos[i]];
            cur[pos[i]] = i;
        }
        debug(cur);
    }
    return res;

}

//----------------------

const ll MOD = 1000000009;
ll mpow (ll bs, ll ep) {
    ll ret = 1;
    while (ep) {
        if (ep&1) ret = ret * bs % MOD;
        ep >>= 1;
        bs = bs * bs % MOD;
    }
    return ret;
}
int countReplacement(int n, int inputSeq[])
{
    if (lvalid(n, inputSeq) == 0) return 0;
    int off = 1;

    vector<int> fin;
    int mul = n, alive = 0;
    for (int i=0; i<n; i++) {
        int x = inputSeq[i];
        if (x > n) {
            fin.eb(x);
        }
        if (x > n) alive++;
        else mul = 1;
    }
    fin.eb(n);
    sort(ALL(fin));
    ll res = 1;
    for (int i=1; i<SZ(fin); i++) {
        int gap = fin[i] - fin[i-1];
        res = res * mpow(alive, gap-1) % MOD;
        alive--;
    }
    return res * mul % MOD;
}
