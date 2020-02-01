#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define REP(i,n) for(int i=0;i<n;i++)
#define REP1(i,n) for(int i=1;i<=n;i++)
#define SZ(i) int(i.size())
#define eb emplace_back
#ifdef tmd
#define debug(...) fprintf(stderr,"%s - %d (%s) = ",__PRETTY_FUNCTION__,__LINE__,#__VA_ARGS__);_do(__VA_ARGS__);
template<typename T> void _do(T &&x){cerr<<x<<endl;}
template<typename T, typename ...S> void _do(T &&x, S &&...y){cerr<<x<<", ";_do(y...);}
#define IOS()
#else
#define debug(...)
#define IOS() ios_base::sync_with_stdio(0);cin.tie(0)
#define endl '\n'
#endif

const int iNF = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int MAXN = 1000006;

typedef pair<ll,int> pli;
ll n, b, c;
multiset<pli> hei;
ll H[MAXN], sum;

void make_left (int i) {
    if (i != 0) {
        if (H[i-1] - H[i] >= c) {
            ll dl = (H[i-1]-(H[i]+c-1)+b-1)/b;
            ll nw = H[i-1]-dl*b;
            sum += dl;
            hei.erase(pli(H[i-1], i-1));
            H[i-1] = nw;
            hei.insert(pli(H[i-1], i-1));
        }
    }
}

void make_right (int i) {
    if (i != n-1) {
        if (H[i+1] - H[i] >= c) {
            ll dl = (H[i+1]-(H[i]+c-1)+b-1)/b;
            ll nw = H[i+1]-dl*b;
            sum += dl;
            hei.erase(pli(H[i+1], i+1));
            H[i+1] = nw;
            hei.insert(pli(H[i+1], i+1));
        }
    }
}
int main () {
    IOS();
    cin >> n >> b >> c;

    c++;
    REP (i, n) {
        ll sz;
        cin >> sz;
        H[i] = sz;
        hei.insert(pli(sz, i));
    }

    REP (i, n) {
        pli sm = *hei.begin();
        debug(sm.first, sm.second);
        make_left(sm.second);
        make_right(sm.second);
        hei.erase(pli(H[sm.second],sm.second));
        #ifdef tmd
        cout << sum << endl;
        REP (j, n) {
            cout << H[j] << " \n"[j==n-1];
        }
        #endif
    }

    cout << sum << endl;

}
