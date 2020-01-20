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

#define X first
#define Y second

int q;
multiset<int> l, r;

bool in (pair<int,int> p1, pair<int,int> p2) {
    return p1.X <= p2.X && p2.Y <= p1.Y;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> q;
    while (q--) {
        int cmd;
        cin >> cmd;
        if (cmd == 1) {
            int L, R;
            cin >> L >> R;
            l.insert(L);
            r.insert(R);
        } else if (cmd == 2) {
            int L, R;
            cin >> L >> R;
            l.erase(l.find(L));
            r.erase(r.find(R));
        } else {
            pair<int,int> r1, r2;
            cin >> r1.X >> r1.Y;
            cin >> r2.X >> r2.Y;

            if (r1 == r2) {
                cout << 0 << endl;
                continue;
            }

            if (r1.Y < r2.X || r1.X > r2.Y) {
                cout << 1 << endl;
                continue;
            }

            bool hl = r.lower_bound(min(r1.X, r2.X)) != r.begin();
            bool hr = l.lower_bound(max(r1.Y, r2.Y)+1) != l.end();

            if (hl || hr) {
                cout << 2 << endl;
                continue;
            }

            if (in(r1,r2) || in(r2,r1)) {
                cout << -1 << endl;
                continue;
            }
            hl = r.lower_bound(max(r1.X, r2.X)) != r.begin();
            hr = l.lower_bound(min(r1.Y, r2.Y)+1) != l.end();

            if (hl && hr) {
                cout << 3 << endl;
            } else {
                cout << -1 << endl;
            }
        }

    }

}
/*
6
1 1 6
1 2 3
1 4 5
1 4 8
1 7 9
3 1 6 4 8
*/
