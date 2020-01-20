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
const ll INF = 1<<31;

int t;
ll k;
string str;

int cnt[26];
int odd;

ll fac[16];
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;

    fac[0] = 1;
    REP1 (i, 15) {
        fac[i] = fac[i-1] * i;
    }

    REP1 (test, t) {
        cin >> str >> k;

        odd = -1;
        for (auto v : str) {
            cnt[v-'a']++;
        }

        bool fail = false;
        REP (i, 26) {
            if (cnt[i] & 1) {
                if (odd != -1) {
                    fail = true;
                } else {
                    odd = i;
                }
            }
            cnt[i] /= 2;
        }

        cout << "Case " << test << ": ";
        if (fail) {
            cout << "XXX" << endl;
        } else {
            string ans;
            int n = SZ(str) / 2;
            REP (i, n) {
                REP (j, 26) {
                    if (cnt[j] == 0) {
                        continue;
                    }
                    cnt[j]--;

                    ll cur = fac[n-i-1];
                    REP (k, 26) {
                        cur /= fac[cnt[k]];
                    }

                    if (cur >= k) {
                        ans += j+'a';
                        break;
                    }
                    k -= cur;

                    cnt[j]++;
                }
            }

            debug(k);
            if (SZ(ans) != n) {
                cout << "XXX" << endl;
            } else {
                cout << ans;
                if (odd != -1) {
                    cout << char(odd + 'a');
                }
                reverse(ans.begin(),ans.end());
                cout << ans << endl;
            }
        }
    }

}
