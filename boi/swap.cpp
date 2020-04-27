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

const int MAXN = 200005;
const ll MOD = 1000000007;

int n, a[MAXN], ans[MAXN];
bool vis[MAXN];

#include <ext/pb_ds/priority_queue.hpp>
typedef __gnu_pbds::priority_queue<int,less<int> > heap;

heap hp[MAXN];

vector<int> bf () {
    vector<int> res;
    for (int i=0; i<(1<<(n-1)); i++) {
        vector<int> cur;
        for (int j=0; j<n; j++) {
            cur.emplace_back(a[j]);
        }
        for (int j=0; j<n-1; j++) {
            if (i & (1<<j)) {
                swap(cur[j+1], cur[j/2]);
            }
        }

        if (res.empty() || cur < res) {
            swap(res, cur);
        }
    }

    return res;
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n;

#ifdef tmd
    
    for (int i=0; i<n; i++) {
        a[i] = i+1;
    }

    srand(time(0));
    random_shuffle(a, a+n);

    for (int i=0; i<n; i++) {
        cout << a[i] << " \n"[i==n-1];
    }
#else

    for (int i=0; i<n; i++) {
        cin >> a[i];
    }

#endif

    for (int i=0; i<n; i++) {
        hp[i].push(a[i]);
    }

    for (int i=0; i<n; i++) {

        heap &pq = hp[i];

        assert(!pq.empty());
        if (i*2 + 1 >= n) {

            ans[i] = pq.top();
            pq.pop();

        } else if (i*2 + 1 == n-1 ) {

            if (pq.top() < a[i*2+1]) {
                ans[i] = pq.top();
                pq.pop();
            } else {
                ans[i] = a[i*2+1];
                vis[i*2+1] = true;
            }

        } else {

            int mn = min({pq.top(), a[i*2+1], a[i*2+2]});

            if (pq.top() == mn) {
                ans[i] = pq.top();
                pq.pop();
            } else if (a[i*2+1] == mn) {
                ans[i] = a[i*2+1];
                vis[i*2+1] = true;
            } else {
                ans[i] = a[i*2+2];
                vis[i*2+1] = true;
                vis[i*2+2] = true;
                pq.emplace(a[i*2+1]);
            }

        }


    }

    if (n <= 20) {
        vector<int> res = bf();
        for (int i=0; i<n; i++) {
            cout << res[i] << " \n"[i==n-1];
        }

        for (int i=0; i<n; i++) {
            cout << ans[i] << " \n"[i==n-1]; 
        }
    } else {
        for (int i=0; i<n; i++) {
            cout << ans[i] << " \n"[i==n-1]; 
        }
    }
    
}

