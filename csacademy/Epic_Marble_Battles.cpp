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
const ll INF = 0x3f3f3f3f3f3f3f3f;

int t;

string str;
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {
        cin >> str;

        string nw = "b";

        int cnta = 0, cntb = 0;
        for (int i=0;i<SZ(str); i++) {
            nw += str[i];
            if (SZ(nw)>=3 && nw.substr(SZ(nw)-3) == "aaa") {
                nw.resize(SZ(nw)-3);
                cnta++;
            }
            if (SZ(nw)>=3 && nw.substr(SZ(nw)-3) == "bab") {
                nw.resize(SZ(nw)-2);
            }
        }
        nw += 'b';

        debug(nw);
        int cur = 0;
        for (auto c : nw) {
            if (c == 'a') {
                cntb += (cur - 1) / 2;
                cur = 0;
            } else {
                cur++;
            }
        }
        cntb += (cur - 1) / 2;
        debug(cnta,  cntb);

        cout << (cnta >= cntb ? "Second" : "First") << endl;
    }

}
