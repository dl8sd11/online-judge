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

typedef int TP;
typedef pair<TP,pii> state;

/*********************GoodLuck***********************/
int main () {
    IOS();

    int t;
    cin >> t;
    while (t--) {
        pii bg, ed;
        cin >> bg.X >> bg.Y >> ed.X >> ed.Y;

        queue<state> bfs;
        bfs.emplace(1, bg);

        bool fnd = false;
        TP ans = 0;
        int cnt = 0;
        while (bfs.size()) {
            cnt++;
            state cur = bfs.front();
            bfs.pop();

            if (cur.Y == ed) {
                assert(fnd == false);
                fnd = true;
                ans = cur.X;
            }

            pii nw = cur.Y;
            int sum = nw.X + nw.Y;

            if (sum <= ed.Y) {
                pii xx = {nw.X, sum};
                bfs.emplace(cur.X*2, xx);
            }
            if (sum <= ed.X) {
                pii xx = {sum, nw.Y};
                bfs.emplace(cur.X*2+1, xx);
            }
        }
        debug(cnt);

        if (fnd) {
            cout << ans << endl;
        } else {
            cout << -1 << endl;
        }
    }
}
/*
5
1 1 1 1
1 1 1 5
1 1 3 6
3 2 3 2
5 2 1 2

18446744073709551614
*/
