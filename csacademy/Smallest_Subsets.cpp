#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#ifdef tmd
#define IOS()
#define debug(...) fprintf(stderr,"#%d: %s = ",__LINE__,#__VA_ARGS__),_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
template<typename It> ostream& _printRng(ostream &os,It bg,It ed)
{
    os<<"{";
    for(It it=bg;it!=ed;it++) {
        os<<(it==bg?"":",")<<*it;
    }
    os<<"}";
    return os;
}
template<typename T> ostream &operator << (ostream &os,vector<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;

int n, a[MAXN], k;
ll base;
int cnt;
vector<ll> res;

void init () {
    cnt = 0;
    res.clear();
}

void gen (int idx, ll sum, ll lim, bool opt) {
    cnt++;
    if (opt) {
        res.emplace_back(sum);
    }
    for (int i=idx;i<n;i++) {
        if (sum+a[i]>lim) {
            break;
        }
        gen(i+1,sum+a[i],lim,opt);
        if (cnt >= k) {
            break;
        }
    }
}
/*
Solution:

binary search for the largest sum using recursive method

to produce the answer

generate set < max_sum

and fill the rest element with max_sum
*/
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> k;
    REP (i, n) {
        cin >> a[i];
        if (a[i] < 0) {
            base += a[i];
            a[i] *= -1;
        }
    }
    debug(base);
    sort(a,a+n);

    ll L = 0, R = MOD * n;
    while (L < R - 1) {
        ll M = (L + R) >> 1;
        init();
        gen(0, 0, M, false);
        debug(M, cnt);
        if (cnt >= k) {
            R = M;
        } else {
            L = M;
        }
    }

    init();
    gen(0, 0, L, true);
    REP (i, k-cnt) {
        res.emplace_back(R);
    }

    sort(res.begin(), res.end());
    for (auto v : res) {
        cout << v + base << endl;
    }
    debug(res.size());
}
