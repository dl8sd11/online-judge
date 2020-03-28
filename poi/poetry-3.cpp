#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
typedef pair<ll,ll> pll;
#define REP(i,n) for(int i=0;i<n;++i)
#define REP1(i,n) for(int i=1;i<=n;++i)
#define SZ(i) int(i.size())
#define eb emplace_back
#define ALL(i) i.begin(),i.end()
#define X first
#define Y second
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

const int MAXN = 1000006;
const ll MOD = 1000000007;

int cnt[MAXN], n , s;
vector<int> id[MAXN];
multiset<pii> rem;

void DEC (int x) {
    rem.erase({cnt[x], x});
    cnt[x]--;
    if (cnt[x] > 0) {
        rem.insert({cnt[x], x});
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> s;

    for (int i=0; i<n; i++) {
        int x;
        cin >> x;
        x++;
        x %= s;
        id[x].eb(i);
        cnt[x]++;
    }

    for (int i=0; i<s; i++) {
        if (cnt[i]) {
            rem.insert({cnt[i], i});
        }
    }

    int bst = 0;
    int sum = 0;
    vector<int> ans;
    for (int i=0; i<n; i++) {
        debug(i, sum);
        if (sum == s - 1) {
            sum = 0;
            bst++;
        }
        if (rem.size() == 1) {
            int x = rem.begin()->Y;

            sum += x;
            sum %= s;
            ans.eb(id[x].back());
            id[x].pop_back();
            DEC(x);
        } else {
            auto tp = *prev(rem.end());
            auto sc = *prev(prev(rem.end()));

            if (i < n-1 && (sum + tp.Y) % s == s - 1) {

                int x = sc.Y;
                sum += x;
                sum %= s;
                ans.eb(id[x].back());
                id[x].pop_back();

                DEC(x);

            } else {
                int x = tp.Y;

                sum += x;
                sum %= s;
                ans.eb(id[x].back());
                id[x].pop_back();
                DEC(x);
            }

        }
    }

    cout << bst << endl;
    REP (i, SZ(ans)) {
        cout << ans[i] + 1 << " \n"[i==SZ(ans)-1];
    }

}
