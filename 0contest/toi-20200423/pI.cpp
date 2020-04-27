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

const int MAXN = 302;
const ll MOD = 1000000007;

map<string, string> nid[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();

    string pt;

    while (cin >> pt) {
        REP (i, MAXN) {
            nid[i].clear();
        }
        bool flag = false;

        vector<string> ans;
        while (pt != "()") {
            pt = pt.substr(1, SZ(pt)-2);
            
            int idx = 0;
            idx = pt.find(',');

            string num = pt.substr(0, idx);
            string path = pt.substr(idx+1);
            debug(num, path);

            int sz = SZ(path);
            if (sz == 0) {
                ans.eb(num);
            }
            if (nid[sz].count(path) == 0) {
                nid[sz][path] = num;
            } else {
                flag = true;
                debug(num, path);
            }
            cin >> pt;
        }

        REP1 (i, MAXN-1) {
            for (auto p : nid[i]) {
                if (nid[i-1].count(p.X.substr(0, SZ(p.X)-1)) == 0) {
                    flag = true;
                    debug(p.X, p.Y);
                }
                ans.eb(p.Y);
            }
        }

        if (flag) {
            cout << "not complete" << endl;
        } else {
            REP (i, SZ(ans)) {
                cout << ans[i] << " \n"[i==SZ(ans)-1];
            }
        }
        
    }


}

