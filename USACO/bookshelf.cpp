#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define int ll
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
template<typename T> ostream &operator << (ostream &os,deque<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> ostream &operator << (ostream &os,multiset<T> &v){return _printRng(os,v.begin(), v.end());}
template<typename T> void pary(T bg, T ed){_printRng(cerr,bg,ed);cerr<<endl;}
#else
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0);
#define endl '\n'
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n, l;
ll h[MAXN], w[MAXN], pre[MAXN];
ll dp[MAXN];

#define X first
#define Y second


/*********************GoodLuck***********************/
signed main () {
    IOS();

    cin >> n >> l;
    REP1 (i, n) {
        cin >> h[i] >> w[i];
        pre[i] = pre[i-1] + w[i];
    }

    deque<int> deq;
    multiset<ll> mn;

    int L = 1;
    for (int i=1; i<=n; i++) {

        while (L<i && pre[i]-pre[L-1]>l) {
            debug(deq.front(), L, dp[L-1]+h[deq.front()]);
            int lst = deq.front();
            mn.erase(mn.find(dp[L-1]+h[deq.front()]));
            if (deq.front() == L) {
                deq.pop_front();
            } else {
                mn.insert(dp[L]+h[deq.front()]);
            }
            L++;
        }

        while (deq.size() && h[deq.back()] <= h[i]) {
            debug(deq.back());
            if (deq.size() == 1) {
                mn.erase(mn.find(dp[L-1]+h[deq.back()]));
            } else {
                int l2 = deq[SZ(deq)-2];
                mn.erase(mn.find(dp[l2]+h[deq.back()]));
            }
            deq.pop_back();
        }

        if (deq.empty()) {
            mn.insert(dp[L-1]+h[i]);
        } else {
            mn.insert(dp[deq.back()]+h[i]);
        }
        deq.emplace_back(i);
        debug(deq, mn);
        dp[i] = *mn.begin();
    }

    pary(dp+1, dp+n+1);
    cout << dp[n] << endl;
}
