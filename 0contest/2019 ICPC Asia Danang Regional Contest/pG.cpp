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

const int MAXN = 100005;
const ll MOD = 1000000007;

int t;
string x;

int bs[11];
/*********************GoodLuck***********************/
int main () {
    IOS();

    bs[1] = 0;
    for (int i=2; i<=10; i++) {
        bs[i] = (i-1)*9 + bs[i-1] + (i-2);
    }
    debug(bs[3]);

    cin >> t;
    while (t--) {
        cin >> x;
        int sum = 0;

        int cnt0 = 0, cnt1 = 0, cnt2 = 0;
        for (auto c : x) {
            if (c == '0') {
                cnt0++;
            } else if (c == '1') {
                if (cnt1 == 1) {
                    cnt2++;
                    sum++;
                } else {
                    cnt1++;
                }
            } else {
                cnt2 ++;
                sum += c - '0';
            }
        }

        int ans = bs[SZ(x)];


        // 20000, 10000
        if (SZ(x) == 1) {
            ans += x.front() - '1';
        } else if (cnt0 == SZ(x)-1) {
            ans += cnt2 ? 1 + sum : 0;
        }else if (cnt1 == 1) {
            ans += cnt2 + sum - (x.back() != '0');
        } else {
            ans += cnt2 + (sum-1) - (x.back() != '0');
        }

        cout << ans << endl;


    }
}
