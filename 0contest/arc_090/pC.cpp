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

const int MAXN = 102;
const ll MOD = 1000000007;
const ll INF = 0x3f3f3f3f3f3f3f3f;

vector<int > perm;
int inc[MAXN], dd[MAXN];
/*********************GoodLuck***********************/
int main () {
    IOS();


    REP (n, 13) {
        perm.resize(n);
        iota(perm.begin(), perm.end(), 1);

        set<pair<int,int> > sum;
        do {
            int imax = 0, dmax = 0;
            for (int i=0;i<n;i++) {
                inc[i] = dd[i] = 1;
                for (int j=0;j<i;j++) {
                    if (perm[j]<perm[i]) {
                        inc[i] = max(inc[i],inc[j] + 1);
                    }
                    if (perm[j] > perm[i]) {
                        dd[i] = max(dd[i], dd[j]+1);
                    }
                }
                imax = max(imax, inc[i]);
                dmax = max(dmax, dd[i]);
            }

//            debug(imax, dmax)
            if (n == 10 && imax == 4 && dmax == 3) {
                debug(perm);
            }
            sum.insert({imax,dmax});
        } while (next_permutation(perm.begin(), perm.end()));

        debug(n);
        for (auto v : sum) {
            cout <<v.first << " " << v.second << endl;
        }
        cout << sum.size() << endl;
    }
}

/*

*/
