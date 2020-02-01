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
#define debug(...)
#define pary(...)
#endif

const int MAXN = 100005;
const ll MOD = 1000000007;

int t, cur, cnt, a, b;
set<int> st;

bool qry (int x) {
    bool res;
    cout << x << endl;

#ifdef tmd
    debug(x, a, b);
    assert(x >= 0 && x < 100);
    for (int i=0;i<10;i++) {
        if ((a+i)%100 == x || (b+10*i)%100 == x) {
            debug("FOUND");
            return 1;
        }
    }
    return 0;
#else
    cin >> res;
#endif
    return res;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> t;
    while (t--) {

    #ifdef tmd
        a = rand() % 100;
        b = rand() % 100;
    #endif // tmd

        cnt = 0;
        cur = 0;
        st.clear();
        for (int i=0; i<11; i++) {
            if (i == 10 && cnt == 1) {
                cnt += qry((*st.begin()) + 10);
                break;
            }
            while (st.count(cur % 10)) {
                cur++;
            }

            if (qry(cur)) {
                cnt++;
                st.insert(cur % 10);
                cur = (cur + 10) % 100;
            }
            cur++;
        }

        debug(cnt);
        assert(cnt == 2);
    }
}
