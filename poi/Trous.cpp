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

const int MAXN = 2000005;
const ll MOD = 1000000007;

int n, s;
ll p;
ll pre[MAXN];

deque<pair<ll,int> > deq;

void del (int x) {
    while (deq.front().second-s+1 < x) {
        deq.pop_front();
    }
}

void add (ll sum, int x) {
    while (deq.size() && deq.back().first < sum) {
        deq.pop_back();
    }
    deq.emplace_back(sum, x);
}

bool check (int l, int r) {
    del(l);
    ll sumLR = pre[r] - pre[l-1];
    return sumLR - deq.front().first <= p;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> p >> s;
    REP1 (i, n) {
        cin >> pre[i];
        pre[i] += pre[i-1];
    }

    int l = 1;
    int ans = 0;
    for (int r=s; r<=n; r++) {
        add(pre[r]-pre[r-s], r);
        while (!check(l, r)) {
            l++;
        }
        ans = max(ans, r - l + 1);
    }

    cout << ans << endl;
}
