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

int n, d, m;
vector<pair<int,int> > jobs;
vector<int> work[MAXN];

bool solve (int mac) {
    int l = 0, r = 0;
    int max_delay = 0;
    REP1 (i, n) {
        while (r < m && jobs[r].first <= i) {
            r++;
        }
        int dl = r - l;
        REP (j, min(dl, mac)) {
            max_delay = max(max_delay, i - jobs[l].first);
            l++;
        }
    }

    return l == m && max_delay <= d;
}

void build (int mac) {
    int l = 0, r = 0;
    REP1 (i, n) {
        while (r < m && jobs[r].first <= i) {
            r++;
        }
        int dl = r - l;
        REP (j, min(dl, mac)) {
            work[i].emplace_back(jobs[l].second);
            l++;
        }
    }
}
/*********************GoodLuck***********************/
int main () {
    IOS();

    cin >> n >> d >> m;
    jobs.resize(m);
    REP (i, m) {
        cin >> jobs[i].first;
        jobs[i].second = i + 1;
    }

    sort(jobs.begin(), jobs.end());
    REP (i, m) {
        debug(jobs[i].first, jobs[i].second);
    }

    int L = 0, R = m;
    while (L < R - 1) {
        int mid = (L + R) >> 1;
        if (solve(mid)) {
            R = mid;
        } else {
            L = mid;
        }
    }

    build(R);

    cout << R << endl;
    REP1 (i, n) {
        for (auto w : work[i]) {
            cout << w << " ";
        }
        cout << 0 << endl;
    }
}
